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
struct TYPE_4__ {int /*<<< orphan*/  color_delay; } ;
struct TYPE_3__ {int /*<<< orphan*/  color_delay; } ;

/* Variables and functions */
 TYPE_2__ COLOURS_NTSC_setup ; 
 TYPE_1__ default_setup ; 

void COLOURS_NTSC_RestoreDefaults(void)
{
	COLOURS_NTSC_setup.color_delay = default_setup.color_delay;
}