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
struct TYPE_2__ {char** container; int /*<<< orphan*/  size; } ;
struct vector_type_qualifier {size_t size; int* q_container; TYPE_1__ ext_name; } ;
struct vector_str {int dummy; } ;
struct cpp_demangle_data {int /*<<< orphan*/  push_qualifier; } ;
typedef  enum type_qualifier { ____Placeholder_type_qualifier } type_qualifier ;

/* Variables and functions */
 int /*<<< orphan*/  DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 int /*<<< orphan*/  PUSH_CV_QUALIFIER ; 
 int /*<<< orphan*/  PUSH_NON_CV_QUALIFIER ; 
#define  TYPE_CMX 137 
#define  TYPE_CST 136 
#define  TYPE_EXT 135 
#define  TYPE_IMG 134 
#define  TYPE_PTR 133 
#define  TYPE_REF 132 
#define  TYPE_RREF 131 
#define  TYPE_RST 130 
#define  TYPE_VAT 129 
#define  TYPE_VEC 128 
 int /*<<< orphan*/  VEC_PUSH_STR (struct vector_str*,char const*) ; 
 int /*<<< orphan*/  cpp_demangle_push_subst_v (struct cpp_demangle_data*,struct vector_str*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 

__attribute__((used)) static int
cpp_demangle_push_type_qualifier(struct cpp_demangle_data *ddata,
    struct vector_type_qualifier *v, const char *type_str)
{
	struct vector_str subst_v;
	enum type_qualifier t;
	size_t idx, e_idx, e_len;
	char *buf;
	int rtn;
	bool cv;

	if (ddata == NULL || v == NULL)
		return (0);

	if ((idx = v->size) == 0)
		return (1);

	rtn = 0;
	if (type_str != NULL) {
		if (!vector_str_init(&subst_v))
			return (0);
		if (!VEC_PUSH_STR(&subst_v, type_str))
			goto clean;
	}

	cv = true;
	e_idx = 0;
	while (idx > 0) {
		switch (v->q_container[idx - 1]) {
		case TYPE_PTR:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (!DEM_PUSH_STR(ddata, "*"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, "*"))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_REF:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (!DEM_PUSH_STR(ddata, "&"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, "&"))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_RREF:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (!DEM_PUSH_STR(ddata, "&&"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, "&&"))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_CMX:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (!DEM_PUSH_STR(ddata, " complex"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, " complex"))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_IMG:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (!DEM_PUSH_STR(ddata, " imaginary"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, " imaginary"))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_EXT:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (v->ext_name.size == 0 ||
			    e_idx > v->ext_name.size - 1)
				goto clean;
			if ((e_len = strlen(v->ext_name.container[e_idx])) ==
			    0)
				goto clean;
			if ((buf = malloc(e_len + 2)) == NULL)
				goto clean;
			snprintf(buf, e_len + 2, " %s",
			    v->ext_name.container[e_idx]);

			if (!DEM_PUSH_STR(ddata, buf)) {
				free(buf);
				goto clean;
			}

			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, buf)) {
					free(buf);
					goto clean;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v)) {
					free(buf);
					goto clean;
				}
			}
			free(buf);
			++e_idx;
			break;

		case TYPE_RST:
			if (ddata->push_qualifier == PUSH_NON_CV_QUALIFIER &&
			    cv)
				break;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER && !cv)
				break;
			if (!DEM_PUSH_STR(ddata, " restrict"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, " restrict"))
					goto clean;
				if (idx - 1 > 0) {
					t = v->q_container[idx - 2];
					if (t == TYPE_RST || t == TYPE_VAT ||
					    t == TYPE_CST)
						break;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_VAT:
			if (ddata->push_qualifier == PUSH_NON_CV_QUALIFIER &&
			    cv)
				break;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER && !cv)
				break;
			if (!DEM_PUSH_STR(ddata, " volatile"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, " volatile"))
					goto clean;
				if (idx - 1 > 0) {
					t = v->q_container[idx - 2];
					if (t == TYPE_RST || t == TYPE_VAT ||
					    t == TYPE_CST)
						break;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_CST:
			if (ddata->push_qualifier == PUSH_NON_CV_QUALIFIER &&
			    cv)
				break;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER && !cv)
				break;
			if (!DEM_PUSH_STR(ddata, " const"))
				goto clean;
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, " const"))
					goto clean;
				if (idx - 1 > 0) {
					t = v->q_container[idx - 2];
					if (t == TYPE_RST || t == TYPE_VAT ||
					    t == TYPE_CST)
						break;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_VEC:
			cv = false;
			if (ddata->push_qualifier == PUSH_CV_QUALIFIER)
				break;
			if (v->ext_name.size == 0 ||
			    e_idx > v->ext_name.size - 1)
				goto clean;
			if ((e_len = strlen(v->ext_name.container[e_idx])) ==
			    0)
				goto clean;
			if ((buf = malloc(e_len + 12)) == NULL)
				goto clean;
			snprintf(buf, e_len + 12, " __vector(%s)",
			    v->ext_name.container[e_idx]);
			if (!DEM_PUSH_STR(ddata, buf)) {
				free(buf);
				goto clean;
			}
			if (type_str != NULL) {
				if (!VEC_PUSH_STR(&subst_v, buf)) {
					free(buf);
					goto clean;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v)) {
					free(buf);
					goto clean;
				}
			}
			free(buf);
			++e_idx;
			break;
		}
		--idx;
	}

	rtn = 1;
clean:
	if (type_str != NULL)
		vector_str_dest(&subst_v);

	return (rtn);
}