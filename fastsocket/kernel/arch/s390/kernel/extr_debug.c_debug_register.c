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
typedef  int /*<<< orphan*/  debug_info_t ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/ * debug_register_mode (char const*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

debug_info_t *debug_register(const char *name, int pages_per_area,
			     int nr_areas, int buf_size)
{
	return debug_register_mode(name, pages_per_area, nr_areas, buf_size,
				   S_IRUSR | S_IWUSR, 0, 0);
}