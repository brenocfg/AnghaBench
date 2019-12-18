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
struct TYPE_2__ {int s_PsndRate; int* KeyBinds; scalar_t__ scaling; scalar_t__ s_PicoCDBuffers; } ;

/* Variables and functions */
 TYPE_1__ defaultConfig ; 

void pemu_prep_defconfig(void)
{
	defaultConfig.s_PsndRate = 22050;
	defaultConfig.s_PicoCDBuffers = 0;
	defaultConfig.KeyBinds[ 2] = 1<<0; // SACB RLDU
	defaultConfig.KeyBinds[ 3] = 1<<1;
	defaultConfig.KeyBinds[ 0] = 1<<2;
	defaultConfig.KeyBinds[ 1] = 1<<3;
	defaultConfig.KeyBinds[ 5] = 1<<4;
	defaultConfig.KeyBinds[ 6] = 1<<5;
	defaultConfig.KeyBinds[ 7] = 1<<6;
	defaultConfig.KeyBinds[ 4] = 1<<7;
	defaultConfig.KeyBinds[13] = 1<<26; // switch rend
	defaultConfig.KeyBinds[ 8] = 1<<27; // save state
	defaultConfig.KeyBinds[ 9] = 1<<28; // load state
	defaultConfig.KeyBinds[12] = 1<<29; // vol up
	defaultConfig.KeyBinds[11] = 1<<30; // vol down
	defaultConfig.scaling = 0;
}