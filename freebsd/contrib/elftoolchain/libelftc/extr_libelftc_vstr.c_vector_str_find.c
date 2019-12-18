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
struct vector_str {size_t size; int /*<<< orphan*/ * container; } ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

int
vector_str_find(const struct vector_str *v, const char *o, size_t l)
{
	size_t i;

	if (v == NULL || o == NULL)
		return (-1);

	for (i = 0; i < v->size; ++i)
		if (strncmp(v->container[i], o, l) == 0)
			return (1);

	return (0);
}