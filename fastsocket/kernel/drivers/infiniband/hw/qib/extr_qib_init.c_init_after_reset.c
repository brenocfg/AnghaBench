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
struct qib_devdata {int num_pports; scalar_t__ pport; int /*<<< orphan*/  (* f_sendctrl ) (scalar_t__,int) ;int /*<<< orphan*/  (* f_rcvctrl ) (scalar_t__,int,int) ;} ;

/* Variables and functions */
 int QIB_RCVCTRL_CTXT_DIS ; 
 int QIB_RCVCTRL_INTRAVAIL_DIS ; 
 int QIB_RCVCTRL_TAILUPD_DIS ; 
 int QIB_SENDCTRL_AVAIL_DIS ; 
 int QIB_SENDCTRL_SEND_DIS ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int) ; 

__attribute__((used)) static int init_after_reset(struct qib_devdata *dd)
{
	int i;

	/*
	 * Ensure chip does no sends or receives, tail updates, or
	 * pioavail updates while we re-initialize.  This is mostly
	 * for the driver data structures, not chip registers.
	 */
	for (i = 0; i < dd->num_pports; ++i) {
		/*
		 * ctxt == -1 means "all contexts". Only really safe for
		 * _dis_abling things, as here.
		 */
		dd->f_rcvctrl(dd->pport + i, QIB_RCVCTRL_CTXT_DIS |
				  QIB_RCVCTRL_INTRAVAIL_DIS |
				  QIB_RCVCTRL_TAILUPD_DIS, -1);
		/* Redundant across ports for some, but no big deal.  */
		dd->f_sendctrl(dd->pport + i, QIB_SENDCTRL_SEND_DIS |
			QIB_SENDCTRL_AVAIL_DIS);
	}

	return 0;
}