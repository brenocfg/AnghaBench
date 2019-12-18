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
struct cpp_demangle_data {int /*<<< orphan*/  cur_output; } ;

/* Variables and functions */
 int vector_str_pop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpp_demangle_pop_str(struct cpp_demangle_data *ddata)
{

	if (ddata == NULL)
		return (0);

	return (vector_str_pop(ddata->cur_output));
}