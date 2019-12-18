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
struct symbol {int dummy; } ;
struct map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine ; 
 struct symbol* machine__find_kernel_function_by_name (int /*<<< orphan*/ *,char const*,struct map**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct symbol *__find_kernel_function_by_name(const char *name,
						     struct map **mapp)
{
	return machine__find_kernel_function_by_name(&machine, name, mapp,
						     NULL);
}