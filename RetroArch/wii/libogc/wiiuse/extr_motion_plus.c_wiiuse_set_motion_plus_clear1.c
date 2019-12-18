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
typedef  int /*<<< orphan*/  uword ;
typedef  int ubyte ;
struct wiimote_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_EXP_MEM_ENABLE1 ; 
 int /*<<< orphan*/  wiiuse_set_motion_plus_clear2 ; 
 int /*<<< orphan*/  wiiuse_write_data (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiiuse_set_motion_plus_clear1(struct wiimote_t *wm,ubyte *data,uword len)
{
	ubyte val = 0x00;
	wiiuse_write_data(wm,WM_EXP_MEM_ENABLE1,&val,1,wiiuse_set_motion_plus_clear2);
}