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
struct ilo_hwinfo {int dummy; } ;
struct TYPE_4__ {char* recv_fifobar; } ;
struct TYPE_3__ {char* send_fifobar; } ;
struct ccb {TYPE_2__ ccb_u3; TYPE_1__ ccb_u1; } ;

/* Variables and functions */
 int SENDQ ; 
 int fifo_enqueue (struct ilo_hwinfo*,char*,int) ; 
 int mk_entry (int,int) ; 

__attribute__((used)) static int ilo_pkt_enqueue(struct ilo_hwinfo *hw, struct ccb *ccb,
			   int dir, int id, int len)
{
	char *fifobar;
	int entry;

	if (dir == SENDQ)
		fifobar = ccb->ccb_u1.send_fifobar;
	else
		fifobar = ccb->ccb_u3.recv_fifobar;

	entry = mk_entry(id, len);
	return fifo_enqueue(hw, fifobar, entry);
}