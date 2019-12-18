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
struct TYPE_2__ {int /*<<< orphan*/  input_dev1; int /*<<< orphan*/  input_dev0; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OPT_SAVECFG_GAME ; 
 int /*<<< orphan*/  PicoGameLoaded ; 
 int /*<<< orphan*/  PicoSetInputDevice (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  e_menu_keyconfig ; 
 int /*<<< orphan*/  me_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_loop (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int menu_loop_keyconfig(int id, int keys)
{
	static int sel = 0;

	me_enable(e_menu_keyconfig, MA_OPT_SAVECFG_GAME, PicoGameLoaded);
	me_loop(e_menu_keyconfig, &sel);

	PicoSetInputDevice(0, currentConfig.input_dev0);
	PicoSetInputDevice(1, currentConfig.input_dev1);

	return 0;
}