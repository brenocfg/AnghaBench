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
struct cpp_demangle_data {int /*<<< orphan*/  subst; } ;

/* Variables and functions */
 int /*<<< orphan*/  vector_str_find (int /*<<< orphan*/ *,char const*,size_t) ; 
 int vector_str_push (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int
cpp_demangle_push_subst(struct cpp_demangle_data *ddata, const char *str,
    size_t len)
{

	if (ddata == NULL || str == NULL || len == 0)
		return (0);

	if (!vector_str_find(&ddata->subst, str, len))
		return (vector_str_push(&ddata->subst, str, len));

	return (1);
}