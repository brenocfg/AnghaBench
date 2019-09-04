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
struct __locale_map {int /*<<< orphan*/  map_size; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 char* __mo_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

const char *__lctrans_impl(const char *msg, const struct __locale_map *lm)
{
	const char *trans = 0;
	if (lm) trans = __mo_lookup(lm->map, lm->map_size, msg);
	return trans ? trans : msg;
}