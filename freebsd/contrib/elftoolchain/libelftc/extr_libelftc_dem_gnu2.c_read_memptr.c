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
 int VEC_PUSH_STR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dest_demangle_data (struct demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int init_demangle_data (struct demangle_data*) ; 
 int read_class (struct demangle_data*) ; 
 int read_qual_name (struct demangle_data*) ; 
 char* vector_str_get_flat (int /*<<< orphan*/ *,size_t*) ; 
 int vector_str_push (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static bool
read_memptr(struct demangle_data *d)
{
	struct demangle_data mptr;
	size_t len;
	bool rtn;
	char *mptr_str;

	if (d == NULL || d->p == NULL)
		return (false);

	if (init_demangle_data(&mptr) == false)
		return (false);

	rtn = false;
	mptr_str = NULL;

	mptr.p = d->p;
	if (*mptr.p == 'Q') {
		++mptr.p;

		if (read_qual_name(&mptr) == false)
			goto clean;
	} else if (read_class(&mptr) == false)
			goto clean;

	d->p = mptr.p;

	if ((mptr_str = vector_str_get_flat(&mptr.vec, &len)) == NULL)
		goto clean;

	if (vector_str_push(&d->vec, mptr_str, len) == false)
		goto clean;

	if (VEC_PUSH_STR(&d->vec, "::*") == false)
		goto clean;

	rtn = true;
clean:
	free(mptr_str);
	dest_demangle_data(&mptr);

	return (rtn);
}