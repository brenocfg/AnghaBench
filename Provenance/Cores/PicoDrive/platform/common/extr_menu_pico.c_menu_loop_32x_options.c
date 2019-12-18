#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int msh2_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_32XOPT_RENDERER ; 
 int /*<<< orphan*/  Pico32xSetClocks (int,int) ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  e_menu_32x_options ; 
 int /*<<< orphan*/  me_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_loop (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ ** renderer_names32x ; 

__attribute__((used)) static int menu_loop_32x_options(int id, int keys)
{
	static int sel = 0;

	me_enable(e_menu_32x_options, MA_32XOPT_RENDERER, renderer_names32x[0] != NULL);
	me_loop(e_menu_32x_options, &sel);

	Pico32xSetClocks(currentConfig.msh2_khz * 1000, currentConfig.msh2_khz * 1000);

	return 0;
}