#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct clcd_fb {TYPE_2__ fb; } ;

/* Variables and functions */
 int CM_CTRL_LCDEN0 ; 
 int CM_CTRL_LCDEN1 ; 
 int CM_CTRL_LCDMUXSEL_MASK ; 
 int CM_CTRL_LCDMUXSEL_VGA_16BPP ; 
 int CM_CTRL_LCDMUXSEL_VGA_8421BPP ; 
 int CM_CTRL_STATIC ; 
 int CM_CTRL_STATIC1 ; 
 int CM_CTRL_STATIC2 ; 
 int CM_CTRL_n24BITEN ; 
 int /*<<< orphan*/  cm_control (int,int) ; 

__attribute__((used)) static void cp_clcd_enable(struct clcd_fb *fb)
{
	u32 val;

	if (fb->fb.var.bits_per_pixel <= 8)
		val = CM_CTRL_LCDMUXSEL_VGA_8421BPP;
	else if (fb->fb.var.bits_per_pixel <= 16)
		val = CM_CTRL_LCDMUXSEL_VGA_16BPP
			| CM_CTRL_LCDEN0 | CM_CTRL_LCDEN1
			| CM_CTRL_STATIC1 | CM_CTRL_STATIC2;
	else
		val = 0; /* no idea for this, don't trust the docs */

	cm_control(CM_CTRL_LCDMUXSEL_MASK|
		   CM_CTRL_LCDEN0|
		   CM_CTRL_LCDEN1|
		   CM_CTRL_STATIC1|
		   CM_CTRL_STATIC2|
		   CM_CTRL_STATIC|
		   CM_CTRL_n24BITEN, val);
}