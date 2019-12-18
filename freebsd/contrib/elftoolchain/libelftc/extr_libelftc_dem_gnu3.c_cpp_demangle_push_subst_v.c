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
struct vector_str {int dummy; } ;
struct cpp_demangle_data {int dummy; } ;

/* Variables and functions */
 int cpp_demangle_push_subst (struct cpp_demangle_data*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* vector_str_get_flat (struct vector_str*,size_t*) ; 

__attribute__((used)) static int
cpp_demangle_push_subst_v(struct cpp_demangle_data *ddata, struct vector_str *v)
{
	size_t str_len;
	int rtn;
	char *str;

	if (ddata == NULL || v == NULL)
		return (0);

	if ((str = vector_str_get_flat(v, &str_len)) == NULL)
		return (0);

	rtn = cpp_demangle_push_subst(ddata, str, str_len);

	free(str);

	return (rtn);
}