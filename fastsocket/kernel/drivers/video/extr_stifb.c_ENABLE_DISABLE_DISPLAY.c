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
 int /*<<< orphan*/  SETUP_HW (struct stifb_info*) ; 
 int /*<<< orphan*/  WRITE_WORD (unsigned int,struct stifb_info*,int) ; 

__attribute__((used)) static void
ENABLE_DISABLE_DISPLAY(struct stifb_info *fb, int enable)
{
	unsigned int value = enable ? 0x43000000 : 0x03000000;
        SETUP_HW(fb);
        WRITE_WORD(0x06000000,	fb, 0x1030);
        WRITE_WORD(value, 	fb, 0x1038);
}