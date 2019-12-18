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
 int /*<<< orphan*/  REG_11 ; 
 int /*<<< orphan*/  REG_12 ; 
 int /*<<< orphan*/  REG_14 ; 
 int /*<<< orphan*/  REG_8 ; 
 int /*<<< orphan*/  SETUP_HW (struct stifb_info*) ; 
 int /*<<< orphan*/  WRITE_WORD (int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SETUP_ATTR_ACCESS(struct stifb_info *fb, unsigned BufferNumber)
{
	SETUP_HW(fb);
	WRITE_WORD(0x2EA0D000, fb, REG_11);
	WRITE_WORD(0x23000302, fb, REG_14);
	WRITE_WORD(BufferNumber, fb, REG_12);
	WRITE_WORD(0xffffffff, fb, REG_8);
}