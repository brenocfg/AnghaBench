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
 int vector_str_pop (int /*<<< orphan*/ *) ; 
 int vector_str_push (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static bool
read_op_user(struct demangle_data *d)
{
	struct demangle_data from, to;
	size_t from_len, to_len;
	bool rtn;
	char *from_str, *to_str;

	if (d == NULL)
		return (false);

	if (init_demangle_data(&from) == false)
		return (false);

	rtn = false;
	from_str = NULL;
	to_str = NULL;
	if (init_demangle_data(&to) == false)
		goto clean;

	to.p = d->p;
	if (*to.p == 'Q') {
		++to.p;

		if (read_qual_name(&to) == false)
			goto clean;

		/* pop last '::' */
		if (vector_str_pop(&to.vec) == false)
			goto clean;
	} else {
		if (read_class(&to) == false)
			goto clean;

		/* skip '__' */
		to.p += 2;
	}

	if ((to_str = vector_str_get_flat(&to.vec, &to_len)) == NULL)
		goto clean;

	from.p = to.p;
	if (*from.p == 'Q') {
		++from.p;

		if (read_qual_name(&from) == false)
			goto clean;

		/* pop last '::' */
		if (vector_str_pop(&from.vec) == false)
			goto clean;
	} else {
		if (read_class(&from) == false)
			goto clean;
	}

	if ((from_str = vector_str_get_flat(&from.vec, &from_len)) == NULL)
		goto clean;

	if (vector_str_push(&d->vec, from_str, from_len) == false)
		goto clean;

	if (VEC_PUSH_STR(&d->vec, "::operator ") == false)
		return (false);

	if (vector_str_push(&d->vec, to_str, to_len) == false)
		goto clean;

	rtn = VEC_PUSH_STR(&d->vec, "()");
clean:
	free(to_str);
	free(from_str);
	dest_demangle_data(&to);
	dest_demangle_data(&from);

	return (rtn);
}