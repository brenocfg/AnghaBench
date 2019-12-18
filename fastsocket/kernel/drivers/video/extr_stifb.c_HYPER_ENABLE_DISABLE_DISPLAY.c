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
struct stifb_info {int dummy; } ;

/* Variables and functions */
 unsigned int READ_WORD (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_33 ; 
 int /*<<< orphan*/  SETUP_HW (struct stifb_info*) ; 
 int /*<<< orphan*/  WRITE_WORD (unsigned int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
HYPER_ENABLE_DISABLE_DISPLAY(struct stifb_info *fb, int enable)
{
	u32 DregsHypMiscVideo = REG_33;
	unsigned int value;
	SETUP_HW(fb);
	value = READ_WORD(fb, DregsHypMiscVideo);
	if (enable)
		value |= 0x0A000000;
	else
		value &= ~0x0A000000;
	WRITE_WORD(value, fb, DregsHypMiscVideo);
}