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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_max_32bit_offset (unsigned int) ; 
 int /*<<< orphan*/  pmap_max_64bit_offset (unsigned int) ; 

vm_map_offset_t pmap_max_offset(
	boolean_t		is64,
	unsigned int	option)
{
	return (is64) ? pmap_max_64bit_offset(option) : pmap_max_32bit_offset(option);
}