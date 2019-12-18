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
typedef  int u8 ;

/* Variables and functions */
 int __ntd_ohci ; 
 int __ntd_ohci_initflag ; 

void __ntd_set_ohci(u8 hci)
{
	if(hci==0x0000) {
		__ntd_ohci = 0;
		__ntd_ohci_initflag = 1;
	} else if(hci==0x0001) {
		__ntd_ohci = 1;
		__ntd_ohci_initflag = 1;
	}
}