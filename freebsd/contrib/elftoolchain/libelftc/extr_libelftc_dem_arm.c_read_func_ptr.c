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
struct demangle_data {char* p; int ptr; int ref; int cnst; int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int CPP_DEMANGLE_ARM_TRY ; 
 int VEC_PUSH_STR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dest_demangle_data (struct demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int init_demangle_data (struct demangle_data*) ; 
 int read_type (struct demangle_data*) ; 
 char* vector_str_get_flat (int /*<<< orphan*/ *,size_t*) ; 
 int vector_str_push (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static bool
read_func_ptr(struct demangle_data *d)
{
	struct demangle_data fptr;
	size_t arg_len, rtn_len;
	char *arg_type, *rtn_type;
	int lim;

	if (d == NULL)
		return (false);

	if (init_demangle_data(&fptr) == false)
		return (false);

	fptr.p = d->p + 1;
	lim = 0;
	arg_type = NULL;
	rtn_type = NULL;

	for (;;) {
		if (read_type(&fptr) == false) {
			dest_demangle_data(&fptr);

			return (false);
		}

		if (fptr.ptr == true) {
			if (VEC_PUSH_STR(&fptr.vec, "*") == false) {
				dest_demangle_data(&fptr);

				return (false);
			}

			fptr.ptr = false;
		}

		if (fptr.ref == true) {
			if (VEC_PUSH_STR(&fptr.vec, "&") == false) {
				dest_demangle_data(&fptr);

				return (false);
			}

			fptr.ref = false;
		}

		if (fptr.cnst == true) {
			if (VEC_PUSH_STR(&fptr.vec, " const") == false) {
				dest_demangle_data(&fptr);

				return (false);
			}

			fptr.cnst = false;
		}

		if (*fptr.p == '_')
			break;

		if (VEC_PUSH_STR(&fptr.vec, ", ") == false) {
			dest_demangle_data(&fptr);

			return (false);
		}

		if (++lim > CPP_DEMANGLE_ARM_TRY) {

			dest_demangle_data(&fptr);

			return (false);
		}
	}

	arg_type = vector_str_get_flat(&fptr.vec, &arg_len);
	/* skip '_' */
	d->p = fptr.p + 1;

	dest_demangle_data(&fptr);

	if (init_demangle_data(&fptr) == false) {
		free(arg_type);

		return (false);
	}

	fptr.p = d->p;
	lim = 0;

	if (read_type(&fptr) == false) {
		free(arg_type);
		dest_demangle_data(&fptr);

		return (false);
	}

	rtn_type = vector_str_get_flat(&fptr.vec, &rtn_len);
	d->p = fptr.p;


	dest_demangle_data(&fptr);

	if (vector_str_push(&d->vec, rtn_type, rtn_len) == false) {
		free(rtn_type);
		free(arg_type);

		return (false);
	}

	free(rtn_type);

	if (VEC_PUSH_STR(&d->vec, " (*)(") == false) {
		free(arg_type);

		return (false);
	}

	if (vector_str_push(&d->vec, arg_type, arg_len) == false) {
		free(arg_type);

		return (false);
	}

	free(arg_type);

	return (VEC_PUSH_STR(&d->vec, ")"));
}