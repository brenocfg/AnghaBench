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
struct inpcb {struct ifnet* inp_last_outifp; } ;
struct ifnet {int dummy; } ;
struct flow_divert_pcb {int /*<<< orphan*/  so; } ;
typedef  int Boolean ;

/* Variables and functions */
 int FALSE ; 
 int IFNET_IS_CELLULAR (struct ifnet*) ; 
 scalar_t__ IFNET_IS_WIFI (struct ifnet*) ; 
 scalar_t__ IFNET_IS_WIRED (struct ifnet*) ; 
 int /*<<< orphan*/  INP_ADD_STAT (struct inpcb*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inp_set_activity_bitmap (struct inpcb*) ; 
 int /*<<< orphan*/  rxbytes ; 
 int /*<<< orphan*/  rxpackets ; 
 struct inpcb* sotoinpcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txbytes ; 
 int /*<<< orphan*/  txpackets ; 

__attribute__((used)) static void
flow_divert_add_data_statistics(struct flow_divert_pcb *fd_cb, int data_len, Boolean send)
{
	struct inpcb *inp = NULL;
	struct ifnet *ifp = NULL;
	Boolean cell = FALSE;
	Boolean wifi = FALSE;
	Boolean wired = FALSE;
	
	inp = sotoinpcb(fd_cb->so);
	if (inp == NULL) {
		return;
	}

	ifp = inp->inp_last_outifp;
	if (ifp != NULL) {
		cell = IFNET_IS_CELLULAR(ifp);
		wifi = (!cell && IFNET_IS_WIFI(ifp));
		wired = (!wifi && IFNET_IS_WIRED(ifp));
	}
	
	if (send) {
		INP_ADD_STAT(inp, cell, wifi, wired, txpackets, 1);
		INP_ADD_STAT(inp, cell, wifi, wired, txbytes, data_len);
	} else {
		INP_ADD_STAT(inp, cell, wifi, wired, rxpackets, 1);
		INP_ADD_STAT(inp, cell, wifi, wired, rxbytes, data_len);
	}
	inp_set_activity_bitmap(inp);
}