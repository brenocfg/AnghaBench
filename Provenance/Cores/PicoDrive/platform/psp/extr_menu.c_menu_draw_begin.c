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

/* Variables and functions */
 int /*<<< orphan*/  GU_DIRECT ; 
 int /*<<< orphan*/  GU_PSM_5650 ; 
 int /*<<< orphan*/  bg_buffer ; 
 int /*<<< orphan*/  guCmdList ; 
 int /*<<< orphan*/  menu_screen ; 
 int /*<<< orphan*/  sceGuCopyImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuFinish () ; 
 int /*<<< orphan*/  sceGuStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void menu_draw_begin(void)
{
	// short *src = (short *)bg_buffer, *dst = (short *)menu_screen;
	// int i;

	// for (i = 272; i >= 0; i--, dst += 512, src += 480)
	//	memcpy32((int *)dst, (int *)src, 480*2/4);

	sceGuSync(0,0); // sync with prev
	sceGuStart(GU_DIRECT, guCmdList);
	sceGuCopyImage(GU_PSM_5650, 0, 0, 480, 272, 480, bg_buffer, 0, 0, 512, menu_screen);
	sceGuFinish();
	sceGuSync(0,0);
}