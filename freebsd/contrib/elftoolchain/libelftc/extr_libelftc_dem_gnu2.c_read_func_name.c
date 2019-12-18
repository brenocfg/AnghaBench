#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; char** container; } ;
struct demangle_data {char* p; scalar_t__ type; int cnst_fn; TYPE_1__ vec; } ;

/* Variables and functions */
 scalar_t__ ELFTC_ISDIGIT (char) ; 
 scalar_t__ ENCODE_FUNC ; 
 scalar_t__ ENCODE_OP ; 
 void* ENCODE_OP_CT ; 
 scalar_t__ ENCODE_OP_DT ; 
 scalar_t__ ENCODE_OP_TF ; 
 scalar_t__ ENCODE_OP_TI ; 
 scalar_t__ ENCODE_OP_USER ; 
 scalar_t__ ENCODE_OP_VT ; 
 int VEC_PUSH_STR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int read_class (struct demangle_data*) ; 
 int read_func (struct demangle_data*) ; 
 int read_op (struct demangle_data*) ; 
 int read_qual_name (struct demangle_data*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 size_t strlen (char*) ; 
 int vector_str_pop (TYPE_1__*) ; 
 int vector_str_push (TYPE_1__*,char*,size_t) ; 

__attribute__((used)) static bool
read_func_name(struct demangle_data *d)
{
	size_t len;
	bool rtn;
	char *op_name;

	if (d == NULL)
		return (false);

	rtn = false;
	op_name = NULL;

	assert(d->p != NULL && "d->p (org str) is NULL");

	if (*d->p == '_' && *(d->p + 1) == '_') {
		d->p += 2;

		/* CTOR */
		if (*d->p == 'Q' && ELFTC_ISDIGIT(*(d->p + 1))) {
			++d->p;
			d->type = ENCODE_OP_CT;

			if (read_qual_name(d) == false)
				return (false);

			return (vector_str_pop(&d->vec));
		} else if (ELFTC_ISDIGIT(*d->p)) {
			d->type = ENCODE_OP_CT;

			return (read_class(d));
		}

		d->type = ENCODE_OP;
		if (read_op(d) == false) {
			/* not good condition, start function name with '__' */
			d->type = ENCODE_FUNC;

			if (VEC_PUSH_STR(&d->vec, "__") == false)
				return (false);
			
			return (read_func(d));
		}

		if (d->type == ENCODE_OP_USER ||
		    d->type == ENCODE_OP_TF ||
		    d->type == ENCODE_OP_TI)
			return (true);

		/* skip "__" */
		d->p += 2;

		if (*d->p == 'C') {
			++d->p;

			d->cnst_fn = true;
		}

		/* assume delimiter is removed */
		if (*d->p == 'Q' && ELFTC_ISDIGIT(*(d->p + 1))) {
			++d->p;

			assert(d->vec.size > 0);

			len = strlen(d->vec.container[d->vec.size - 1]);
			if ((op_name = malloc(sizeof(char) * (len + 1)))
			    == NULL)
				return (false);

			snprintf(op_name, len + 1, "%s",
			    d->vec.container[d->vec.size - 1]);
			vector_str_pop(&d->vec);

			if (read_qual_name(d) == false)
				goto clean;

			if (VEC_PUSH_STR(&d->vec, "::") == false)
				goto clean;

			if (vector_str_push(&d->vec, op_name, len) == false)
				goto clean;

			rtn = true;
		} else if (ELFTC_ISDIGIT(*d->p)) {
			assert(d->vec.size > 0);

			len = strlen(d->vec.container[d->vec.size - 1]);
			if ((op_name = malloc(sizeof(char) * (len + 1)))
			    == NULL)
				return (false);

			snprintf(op_name, len + 1, "%s",
			    d->vec.container[d->vec.size - 1]);
			vector_str_pop(&d->vec);

			if (read_class(d) == false)
				goto clean;

			if (VEC_PUSH_STR(&d->vec, "::") == false)
				goto clean;

			if (vector_str_push(&d->vec, op_name, len) == false)
				goto clean;

			rtn = true;
		}
	} else if (memcmp(d->p, "_$_", 3) == 0) {
		/* DTOR */
		d->p += 3;
		d->type = ENCODE_OP_DT;

		if (*d->p == 'Q' && ELFTC_ISDIGIT(*(d->p + 1))) {
			++d->p;

			if (read_qual_name(d) == false)
				return (false);

			return (vector_str_pop(&d->vec));
		} else if (ELFTC_ISDIGIT(*d->p))
			return (read_class(d));

		return (false);
	} else if (memcmp(d->p, "_vt$", 4) == 0) {
		/* vtable */
		d->p += 4;
		d->type = ENCODE_OP_VT;

		if (*d->p == 'Q' && ELFTC_ISDIGIT(*(d->p + 1))) {
			++d->p;

			if (read_qual_name(d) == false)
				return (false);

			if (vector_str_pop(&d->vec) == false)
				return (false);
		} else if (ELFTC_ISDIGIT(*d->p)) {
			if (read_class(d) == false)
				return (false);
		}

		return (VEC_PUSH_STR(&d->vec, " virtual table"));
	} else
		return (read_func(d));
clean:
	free(op_name);

	return (rtn);
}