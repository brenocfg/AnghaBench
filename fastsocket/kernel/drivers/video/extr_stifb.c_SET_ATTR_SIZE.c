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
struct stifb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_6 ; 
 int /*<<< orphan*/  REG_9 ; 
 int /*<<< orphan*/  WRITE_WORD (int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SET_ATTR_SIZE(struct stifb_info *fb, int width, int height) 
{
	/* REG_6 seems to have special values when run on a 
	   RDI precisionbook parisc laptop (INTERNAL_EG_DX1024 or
	   INTERNAL_EG_X1024).  The values are:
		0x2f0: internal (LCD) & external display enabled
		0x2a0: external display only
		0x000: zero on standard artist graphic cards
	*/ 
	WRITE_WORD(0x00000000, fb, REG_6);
	WRITE_WORD((width<<16) | height, fb, REG_9);
	WRITE_WORD(0x05000000, fb, REG_6);
	WRITE_WORD(0x00040001, fb, REG_9);
}