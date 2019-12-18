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
typedef  int u32 ;
struct ti_ohci {int dummy; } ;
struct TYPE_3__ {unsigned char* kvirt; } ;
struct dma_iso_ctx {int buf_size; int syt_offset; int* next_buffer; int* last_used_cmd; int /*<<< orphan*/  packet_size; TYPE_2__** it_prg; TYPE_1__ dma; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 int /*<<< orphan*/  curr ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int reg_read (struct ti_ohci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void put_timestamp(struct ti_ohci *ohci, struct dma_iso_ctx * d,
				 int n)
{
	unsigned char* buf = d->dma.kvirt + n * d->buf_size;
	u32 cycleTimer;
	u32 timeStamp;

	if (n == -1) {
	  return;
	}

	cycleTimer = reg_read(ohci, OHCI1394_IsochronousCycleTimer);

	timeStamp = ((cycleTimer & 0x0fff) + d->syt_offset); /* 11059 = 450 us */
	timeStamp = (timeStamp % 3072 + ((timeStamp / 3072) << 12)
		+ (cycleTimer & 0xf000)) & 0xffff;

	buf[6] = timeStamp >> 8;
	buf[7] = timeStamp & 0xff;

    /* if first packet is empty packet, then put timestamp into the next full one too */
    if ( (le32_to_cpu(d->it_prg[n][0].data[1]) >>16) == 0x008) {
   	    buf += d->packet_size;
    	buf[6] = timeStamp >> 8;
	    buf[7] = timeStamp & 0xff;
	}

    /* do the next buffer frame too in case of irq latency */
	n = d->next_buffer[n];
	if (n == -1) {
	  return;
	}
	buf = d->dma.kvirt + n * d->buf_size;

	timeStamp += (d->last_used_cmd[n] << 12) & 0xffff;

	buf[6] = timeStamp >> 8;
	buf[7] = timeStamp & 0xff;

    /* if first packet is empty packet, then put timestamp into the next full one too */
    if ( (le32_to_cpu(d->it_prg[n][0].data[1]) >>16) == 0x008) {
   	    buf += d->packet_size;
    	buf[6] = timeStamp >> 8;
	    buf[7] = timeStamp & 0xff;
	}

#if 0
	printk("curr: %d, next: %d, cycleTimer: %08x timeStamp: %08x\n",
	       curr, n, cycleTimer, timeStamp);
#endif
}