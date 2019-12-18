#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dmabuf {unsigned int sample_rate; int ready; int mapped; int buforder; int cnt_factor; int sample_size; int num_channels; int src_factor; int user_bytes_per_sample; int dma_bytes_per_sample; int ossfragshift; int fragshift; int subdivision; int fragsize; int dma_fragsize; unsigned int numfrag; int ossmaxfrags; int dmasize; scalar_t__ rawbuf; scalar_t__ nextOut; scalar_t__ nextIn; scalar_t__ dma_qcount; scalar_t__ count; } ;
struct au1550_state {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* ld2 (unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 

__attribute__((used)) static int
prog_dmabuf(struct au1550_state *s, struct dmabuf *db)
{
	unsigned user_bytes_per_sec;
	unsigned        bufs;
	unsigned        rate = db->sample_rate;

	if (!db->rawbuf) {
		db->ready = db->mapped = 0;
		db->buforder = 5;	/* 32 * PAGE_SIZE */
		db->rawbuf = kmalloc((PAGE_SIZE << db->buforder), GFP_KERNEL);
		if (!db->rawbuf)
			return -ENOMEM;
	}

	db->cnt_factor = 1;
	if (db->sample_size == 8)
		db->cnt_factor *= 2;
	if (db->num_channels == 1)
		db->cnt_factor *= 2;
	db->cnt_factor *= db->src_factor;

	db->count = 0;
	db->dma_qcount = 0;
	db->nextIn = db->nextOut = db->rawbuf;

	db->user_bytes_per_sample = (db->sample_size>>3) * db->num_channels;
	db->dma_bytes_per_sample = 2 * ((db->num_channels == 1) ?
					2 : db->num_channels);

	user_bytes_per_sec = rate * db->user_bytes_per_sample;
	bufs = PAGE_SIZE << db->buforder;
	if (db->ossfragshift) {
		if ((1000 << db->ossfragshift) < user_bytes_per_sec)
			db->fragshift = ld2(user_bytes_per_sec/1000);
		else
			db->fragshift = db->ossfragshift;
	} else {
		db->fragshift = ld2(user_bytes_per_sec / 100 /
				    (db->subdivision ? db->subdivision : 1));
		if (db->fragshift < 3)
			db->fragshift = 3;
	}

	db->fragsize = 1 << db->fragshift;
	db->dma_fragsize = db->fragsize * db->cnt_factor;
	db->numfrag = bufs / db->dma_fragsize;

	while (db->numfrag < 4 && db->fragshift > 3) {
		db->fragshift--;
		db->fragsize = 1 << db->fragshift;
		db->dma_fragsize = db->fragsize * db->cnt_factor;
		db->numfrag = bufs / db->dma_fragsize;
	}

	if (db->ossmaxfrags >= 4 && db->ossmaxfrags < db->numfrag)
		db->numfrag = db->ossmaxfrags;

	db->dmasize = db->dma_fragsize * db->numfrag;
	memset(db->rawbuf, 0, bufs);

	pr_debug("prog_dmabuf: rate=%d, samplesize=%d, channels=%d\n",
	    rate, db->sample_size, db->num_channels);
	pr_debug("prog_dmabuf: fragsize=%d, cnt_factor=%d, dma_fragsize=%d\n",
	    db->fragsize, db->cnt_factor, db->dma_fragsize);
	pr_debug("prog_dmabuf: numfrag=%d, dmasize=%d\n", db->numfrag, db->dmasize);

	db->ready = 1;
	return 0;
}