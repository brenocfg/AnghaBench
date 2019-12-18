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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int PAD_ENABLEDMASK (int /*<<< orphan*/ ) ; 
 int SI_ERROR_NO_RESPONSE ; 
 int /*<<< orphan*/  __pad_disable (int /*<<< orphan*/ ) ; 
 int __pad_enabledbits ; 
 int /*<<< orphan*/  __pad_updateorigin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pad_originupdatecallback(s32 chan,u32 type)
{
	u32 en_bits = __pad_enabledbits&PAD_ENABLEDMASK(chan);

	if(en_bits) {
		if(!(type&0x0f)) __pad_updateorigin(chan);
		if(type&SI_ERROR_NO_RESPONSE) __pad_disable(chan);
	}
}