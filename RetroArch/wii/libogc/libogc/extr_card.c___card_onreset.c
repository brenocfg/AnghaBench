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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_SLOTA ; 
 int /*<<< orphan*/  CARD_SLOTB ; 
 int CARD_Unmount (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 

__attribute__((used)) static s32 __card_onreset(s32 final)
{
	if(final==FALSE) {
		if(CARD_Unmount(CARD_SLOTA)==-1) return 0;
		if(CARD_Unmount(CARD_SLOTB)==-1) return 0;
	}
	return 1;
}