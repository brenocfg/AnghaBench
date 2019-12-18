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
struct mode_info {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ VIDEO_FIRST_BIOS ; 
 int set_bios_mode (scalar_t__) ; 

__attribute__((used)) static int bios_set_mode(struct mode_info *mi)
{
	return set_bios_mode(mi->mode - VIDEO_FIRST_BIOS);
}