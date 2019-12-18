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
struct TYPE_2__ {char** container; } ;
struct demangle_data {int* p; TYPE_1__ vec; TYPE_1__ arg; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int VEC_PUSH_STR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 size_t strtol (int*,char**,int) ; 

__attribute__((used)) static int
read_subst_iter(struct demangle_data *d)
{
	int i;
	size_t idx;
	char repeat;
	char *str;

	if (d == NULL)
		return (-1);

	++d->p;
	assert(*d->p > 48 && *d->p < 58 && "*d->p not in ASCII numeric range");

	repeat = *d->p - 48;

	assert(repeat > 1);

	++d->p;

	idx = strtol(d->p, &str, 10);
	if (idx == 0 && (errno == EINVAL || errno == ERANGE))
		return (-1);

	assert(idx > 0);
	assert(str != NULL);

	d->p = str;

	for (i = 0; i < repeat ; ++i) {
		if (VEC_PUSH_STR(&d->vec, d->arg.container[idx - 1]) == false)
			return (-1);

		if (VEC_PUSH_STR(&d->arg, d->arg.container[idx - 1]) == false)
			return (-1);

		if (i != repeat - 1 &&
		    VEC_PUSH_STR(&d->vec, ", ") == false)
			return (-1);
	}

	if (*d->p == '\0')
		return (1);

	return (0);
}