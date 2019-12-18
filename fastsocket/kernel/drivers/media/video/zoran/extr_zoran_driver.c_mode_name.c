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
typedef  enum zoran_map_mode { ____Placeholder_zoran_map_mode } zoran_map_mode ;

/* Variables and functions */
 int ZORAN_MAP_MODE_RAW ; 

__attribute__((used)) static inline const char *mode_name(enum zoran_map_mode mode)
{
	return mode == ZORAN_MAP_MODE_RAW ? "V4L" : "JPG";
}