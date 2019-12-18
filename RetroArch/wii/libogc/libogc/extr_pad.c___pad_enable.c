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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ENABLEDMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_EnablePolling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_GetResponse (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SI_SetCommand (int /*<<< orphan*/ ,int) ; 
 int __pad_analogmode ; 
 int /*<<< orphan*/  __pad_enabledbits ; 

__attribute__((used)) static void __pad_enable(u32 chan)
{
	u32 buf[2];
	__pad_enabledbits |= PAD_ENABLEDMASK(chan);
	SI_GetResponse(chan,(void*)buf);
	SI_SetCommand(chan,(__pad_analogmode|0x00400000));
	SI_EnablePolling(__pad_enabledbits);
}