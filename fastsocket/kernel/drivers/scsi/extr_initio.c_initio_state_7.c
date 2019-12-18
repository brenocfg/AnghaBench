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
struct initio_host {int phase; scalar_t__ addr; } ;

/* Variables and functions */
#define  DATA_IN 129 
#define  DATA_OUT 128 
 scalar_t__ TUL_SFifo ; 
 scalar_t__ TUL_SFifoCnt ; 
 int inb (scalar_t__) ; 
 int initio_bad_seq (struct initio_host*) ; 
 int /*<<< orphan*/  printk (char*) ; 

int initio_state_7(struct initio_host * host)
{
	int cnt, i;

#if DEBUG_STATE
	printk("-s7-");
#endif
	/* flush SCSI FIFO */
	cnt = inb(host->addr + TUL_SFifoCnt) & 0x1F;
	if (cnt) {
		for (i = 0; i < cnt; i++)
			inb(host->addr + TUL_SFifo);
	}
	switch (host->phase) {
	case DATA_IN:		/* Data in phase                */
	case DATA_OUT:		/* Data out phase               */
		return initio_bad_seq(host);
	default:
		return 6;	/* Go to state 6                */
	}
}