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
struct demangle_data {char* p; int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 scalar_t__ ELFTC_ISDIGIT (char) ; 
 int VEC_PUSH_STR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int read_class (struct demangle_data*) ; 
 int read_qual_name (struct demangle_data*) ; 
 char* strstr (char*,char*) ; 
 int vector_str_push (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static bool
read_func(struct demangle_data *d)
{
	size_t len;
	const char *name;
	char *delim;

	if (d == NULL)
		return (false);

	assert(d->p != NULL && "d->p (org str) is NULL");
	if ((delim = strstr(d->p, "__")) == NULL)
		return (false);

	len = delim - d->p;
	assert(len != 0);

	name = d->p;

	d->p = delim + 2;

	if (*d->p == 'Q' && ELFTC_ISDIGIT(*(d->p + 1))) {
		++d->p;

		if (read_qual_name(d) == false)
			return (false);
	} else if (ELFTC_ISDIGIT(*d->p)) {
		if (read_class(d) == false)
			return (false);

		if (VEC_PUSH_STR(&d->vec, "::") == false)
			return (false);
	}

	if (vector_str_push(&d->vec, name, len) == false)
		return (false);

	return (true);
}