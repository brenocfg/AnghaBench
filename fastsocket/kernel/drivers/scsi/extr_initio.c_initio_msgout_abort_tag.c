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
struct initio_host {scalar_t__ phase; scalar_t__ addr; } ;

/* Variables and functions */
 int MSG_ABORT_TAG ; 
 scalar_t__ MSG_OUT ; 
 int TSC_SET_ACK ; 
 int TSC_SET_ATN ; 
 int TSC_XF_FIFO_OUT ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SFifo ; 
 scalar_t__ TUL_SSignal ; 
 int inb (scalar_t__) ; 
 int initio_bad_seq (struct initio_host*) ; 
 int initio_msgin_accept (struct initio_host*) ; 
 int initio_wait_disc (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int initio_msgout_abort_tag(struct initio_host * host)
{

	outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addr + TUL_SSignal);
	if (initio_msgin_accept(host) == -1)
		return -1;
	if (host->phase != MSG_OUT)
		return initio_bad_seq(host);

	outb(MSG_ABORT_TAG, host->addr + TUL_SFifo);
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);

	return initio_wait_disc(host);

}