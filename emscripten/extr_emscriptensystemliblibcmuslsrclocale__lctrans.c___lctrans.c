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
struct __locale_map {int dummy; } ;

/* Variables and functions */
 char const* __lctrans_impl (char const*,struct __locale_map const*) ; 

const char *__lctrans(const char *msg, const struct __locale_map *lm)
{
	return __lctrans_impl(msg, lm);
}