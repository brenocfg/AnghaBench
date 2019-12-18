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
struct aiptek_map {int value; char const* string; } ;

/* Variables and functions */
 int AIPTEK_INVALID_VALUE ; 

__attribute__((used)) static const char *map_val_to_str(const struct aiptek_map *map, int val)
{
	const struct aiptek_map *p;

	for (p = map; p->value != AIPTEK_INVALID_VALUE; p++)
		if (val == p->value)
			return p->string;

	return "unknown";
}