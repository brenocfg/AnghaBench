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
 int hb_preset_version_major ; 
 int hb_preset_version_micro ; 
 int hb_preset_version_minor ; 

void hb_presets_current_version(int *major, int* minor, int *micro)
{
    *major = hb_preset_version_major;
    *minor = hb_preset_version_minor;
    *micro = hb_preset_version_micro;
}