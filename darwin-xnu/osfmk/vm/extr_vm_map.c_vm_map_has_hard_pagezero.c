#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ min_offset; } ;

/* Variables and functions */

boolean_t
vm_map_has_hard_pagezero(
		vm_map_t 	map,
		vm_map_offset_t	pagezero_size)
{
	/*
	 * XXX FBDP
	 * We should lock the VM map (for read) here but we can get away
	 * with it for now because there can't really be any race condition:
	 * the VM map's min_offset is changed only when the VM map is created
	 * and when the zero page is established (when the binary gets loaded),
	 * and this routine gets called only when the task terminates and the
	 * VM map is being torn down, and when a new map is created via
	 * load_machfile()/execve().
	 */
	return (map->min_offset >= pagezero_size);
}