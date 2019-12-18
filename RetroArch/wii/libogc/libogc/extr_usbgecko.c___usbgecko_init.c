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
typedef  size_t u32 ;

/* Variables and functions */
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int usbgecko_inited ; 
 int /*<<< orphan*/ * wait_exi_queue ; 

__attribute__((used)) static void __usbgecko_init()
{
	u32 i;

	for(i=0;i<EXI_CHANNEL_2;i++) {
		LWP_InitQueue(&wait_exi_queue[i]);
	}
	usbgecko_inited = 1;
}