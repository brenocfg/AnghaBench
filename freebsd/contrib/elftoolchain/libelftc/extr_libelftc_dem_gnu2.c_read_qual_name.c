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
struct demangle_data {int* p; int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int VEC_PUSH_STR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int read_class (struct demangle_data*) ; 

__attribute__((used)) static bool
read_qual_name(struct demangle_data *d)
{
	int i;
	char num;

	if (d == NULL)
		return (false);

	assert(d->p != NULL && "d->p (org str) is NULL");
	assert(*d->p > 48 && *d->p < 58 && "*d->p not in ASCII numeric range");

	num = *d->p - 48;

	assert(num > 0);

	++d->p;
	for (i = 0; i < num ; ++i) {
		if (read_class(d) == false)
			return (false);

		if (VEC_PUSH_STR(&d->vec, "::") == false)
			return (false);
	}

	if (*d->p != '\0')
		d->p = d->p + 2;

	return (true);
}