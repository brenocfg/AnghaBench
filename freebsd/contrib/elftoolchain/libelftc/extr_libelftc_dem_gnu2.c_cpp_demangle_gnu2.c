#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t size; } ;
struct TYPE_8__ {char* buf; size_t size; } ;
struct demangle_data {char const* p; int type; int class_name; int ptr; int ref; int cnst; int array; int cnst_fn; TYPE_1__ vec; TYPE_1__ arg; TYPE_5__ array_str; } ;

/* Variables and functions */
 unsigned int CPP_DEMANGLE_GNU2_TRY ; 
#define  ENCODE_FUNC 135 
#define  ENCODE_OP 134 
#define  ENCODE_OP_CT 133 
#define  ENCODE_OP_DT 132 
#define  ENCODE_OP_TF 131 
#define  ENCODE_OP_TI 130 
#define  ENCODE_OP_USER 129 
#define  ENCODE_OP_VT 128 
 int VEC_PUSH_STR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dest_cstring (TYPE_5__*) ; 
 int /*<<< orphan*/  dest_demangle_data (struct demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int init_demangle_data (struct demangle_data*) ; 
 int push_CTDT (char*,int,TYPE_1__*) ; 
 int read_func_name (struct demangle_data*) ; 
 int read_subst (struct demangle_data*) ; 
 int read_subst_iter (struct demangle_data*) ; 
 int read_type (struct demangle_data*) ; 
 char* vector_str_get_flat (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int vector_str_push (TYPE_1__*,char*,size_t) ; 
 char* vector_str_substr (TYPE_1__*,size_t,int,size_t*) ; 

char *
cpp_demangle_gnu2(const char *org)
{
	struct demangle_data d;
	size_t arg_begin, arg_len;
	unsigned int try;
	char *rtn, *arg;

	if (org == NULL)
		return (NULL);

	if (init_demangle_data(&d) == false)
		return (NULL);

	try = 0;
	rtn = NULL;

	d.p = org;
	if (read_func_name(&d) == false)
		goto clean;

	switch (d.type) {
	case ENCODE_FUNC :
	case ENCODE_OP :
		break;

	case ENCODE_OP_CT :
		if (push_CTDT("::", 2, &d.vec) == false)
			goto clean;

                break;
	case ENCODE_OP_DT :
		if (push_CTDT("::~", 3, &d.vec) == false)
			goto clean;

		if (VEC_PUSH_STR(&d.vec, "(void)") == false)
			goto clean;

		goto flat;
	case ENCODE_OP_USER :
	case ENCODE_OP_TF :
	case ENCODE_OP_TI :
	case ENCODE_OP_VT :
		goto flat;
	}

	if (*d.p == 'F')
		++d.p;
	else if (*d.p == '\0') {
		if (d.class_name == true) {
			if (VEC_PUSH_STR(&d.vec, "(void)") == false)
				goto clean;

			goto flat;
		} else
			goto clean;
	}

	/* start argument types */
	if (VEC_PUSH_STR(&d.vec, "(") == false)
		goto clean;

	for (;;) {
		if (*d.p == 'T') {
			const int rtn_subst = read_subst(&d);

			if (rtn_subst == -1)
				goto clean;
			else if (rtn_subst == 1)
				break;

			continue;
		}

		if (*d.p == 'N') {
			const int rtn_subst_iter = read_subst_iter(&d);

			if (rtn_subst_iter == -1)
				goto clean;
			else if(rtn_subst_iter == 1)
				break;

			continue;
		}

		arg_begin = d.vec.size;

		if (read_type(&d) == false)
			goto clean;

		if (d.ptr == true) {
			if (VEC_PUSH_STR(&d.vec, "*") == false)
				goto clean;

			d.ptr = false;
		}

		if (d.ref == true) {
			if (VEC_PUSH_STR(&d.vec, "&") == false)
				goto clean;

			d.ref = false;
		}

		if (d.cnst == true) {
			if (VEC_PUSH_STR(&d.vec, " const") == false)
				goto clean;

			d.cnst = false;
		}

		if (d.array == true) {
			if (vector_str_push(&d.vec, d.array_str.buf,
				d.array_str.size) == false)
				goto clean;

			dest_cstring(&d.array_str);
			d.array = false;
		}

		if (*d.p == '\0')
			break;

		if ((arg = vector_str_substr(&d.vec, arg_begin, d.vec.size - 1,
			    &arg_len)) == NULL)
			goto clean;

		if (vector_str_push(&d.arg, arg, arg_len) == false)
			goto clean;

		free(arg);

		if (VEC_PUSH_STR(&d.vec, ", ") == false)
			goto clean;

		if (++try > CPP_DEMANGLE_GNU2_TRY)
			goto clean;
	}

	/* end argument types */
	if (VEC_PUSH_STR(&d.vec, ")") == false)
		goto clean;
flat:
	if (d.cnst_fn == true && VEC_PUSH_STR(&d.vec, " const") == false)
		goto clean;

	rtn = vector_str_get_flat(&d.vec, NULL);
clean:
	dest_demangle_data(&d);

	return (rtn);
}