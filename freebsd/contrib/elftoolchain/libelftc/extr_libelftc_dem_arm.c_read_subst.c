#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * container; } ;
struct demangle_data {char* p; TYPE_1__ arg; TYPE_1__ vec; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int VEC_PUSH_STR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 size_t strtol (char*,char**,int) ; 

__attribute__((used)) static int
read_subst(struct demangle_data *d)
{
	size_t idx;
	char *str;

	if (d == NULL)
		return (-1);

	idx = strtol(d->p + 1, &str, 10);
	if (idx == 0 && (errno == EINVAL || errno == ERANGE))
		return (-1);

	assert(idx > 0);
	assert(str != NULL);

	d->p = str;

	if (VEC_PUSH_STR(&d->vec, d->arg.container[idx - 1]) == false)
		return (-1);

	if (VEC_PUSH_STR(&d->arg, d->arg.container[idx - 1]) == false)
		return (-1);

	if (*d->p == '\0')
		return (1);

	return (0);
}