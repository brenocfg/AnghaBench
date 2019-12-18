#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skb_shared_info {int nr_frags; TYPE_1__* frags; } ;
struct pkt_gl {int nfrags; TYPE_2__* frags; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int /*<<< orphan*/  page; scalar_t__ size; scalar_t__ page_offset; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ page_offset; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,unsigned int) ; 

__attribute__((used)) static inline void copy_frags(struct skb_shared_info *ssi,
			      const struct pkt_gl *gl, unsigned int offset)
{
	unsigned int n;

	/* usually there's just one frag */
	ssi->frags[0].page = gl->frags[0].page;
	ssi->frags[0].page_offset = gl->frags[0].page_offset + offset;
	ssi->frags[0].size = gl->frags[0].size - offset;
	ssi->nr_frags = gl->nfrags;
	n = gl->nfrags - 1;
	if (n)
		memcpy(&ssi->frags[1], &gl->frags[1], n * sizeof(skb_frag_t));

	/* get a reference to the last page, we don't own it */
	get_page(gl->frags[n].page);
}