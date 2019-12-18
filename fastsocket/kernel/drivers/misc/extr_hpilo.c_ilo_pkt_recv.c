#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ilo_hwinfo {int dummy; } ;
struct TYPE_2__ {char* recv_fifobar; } ;
struct ccb {TYPE_1__ ccb_u3; } ;

/* Variables and functions */
 int fifo_check_recv (struct ilo_hwinfo*,char*) ; 

__attribute__((used)) static int ilo_pkt_recv(struct ilo_hwinfo *hw, struct ccb *ccb)
{
	char *fifobar = ccb->ccb_u3.recv_fifobar;

	return fifo_check_recv(hw, fifobar);
}