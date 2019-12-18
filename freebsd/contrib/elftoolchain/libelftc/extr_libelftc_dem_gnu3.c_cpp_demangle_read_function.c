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
struct vector_type_qualifier {size_t size; scalar_t__* q_container; } ;
struct type_delimit {int paren; int firstp; } ;
struct read_cmd_item {struct vector_type_qualifier* data; } ;
struct TYPE_2__ {size_t size; char** container; } ;
struct cpp_demangle_data {float* cur; int is_functype; int ref_qualifier; int ref_qualifier_type; void* push_qualifier; int /*<<< orphan*/  func_type; TYPE_1__ class_type; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DEMANGLE_TRY_LIMIT ; 
 int /*<<< orphan*/  DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 void* PUSH_ALL_QUALIFIER ; 
 void* PUSH_CV_QUALIFIER ; 
 void* PUSH_NON_CV_QUALIFIER ; 
 int /*<<< orphan*/  READ_PTRMEM ; 
 scalar_t__ TYPE_CST ; 
#define  TYPE_REF 129 
#define  TYPE_RREF 128 
 scalar_t__ TYPE_RST ; 
 scalar_t__ TYPE_VAT ; 
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char const*,size_t) ; 
 int /*<<< orphan*/  cpp_demangle_push_type_qualifier (struct cpp_demangle_data*,struct vector_type_qualifier*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpp_demangle_read_type (struct cpp_demangle_data*,struct type_delimit*) ; 
 size_t strlen (char const*) ; 
 struct read_cmd_item* vector_read_cmd_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_type_qualifier_dest (struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_type_qualifier_init (struct vector_type_qualifier*) ; 

__attribute__((used)) static int
cpp_demangle_read_function(struct cpp_demangle_data *ddata, int *ext_c,
    struct vector_type_qualifier *v)
{
	struct type_delimit td;
	struct read_cmd_item *rc;
	size_t class_type_size, class_type_len, limit;
	const char *class_type;
	int i;
	bool paren, non_cv_qualifier;

	if (ddata == NULL || *ddata->cur != 'F' || v == NULL)
		return (0);

	++ddata->cur;
	if (*ddata->cur == 'Y') {
		if (ext_c != NULL)
			*ext_c = 1;
		++ddata->cur;
	}

	/* Return type */
	if (!cpp_demangle_read_type(ddata, NULL))
		return (0);

	if (*ddata->cur != 'E') {
		if (!DEM_PUSH_STR(ddata, " "))
			return (0);

		non_cv_qualifier = false;
		if (v->size > 0) {
			for (i = 0; (size_t) i < v->size; i++) {
				if (v->q_container[i] != TYPE_RST &&
				    v->q_container[i] != TYPE_VAT &&
				    v->q_container[i] != TYPE_CST) {
					non_cv_qualifier = true;
					break;
				}
			}
		}

		paren = false;
		rc = vector_read_cmd_find(&ddata->cmd, READ_PTRMEM);
		if (non_cv_qualifier || rc != NULL) {
			if (!DEM_PUSH_STR(ddata, "("))
				return (0);
			paren = true;
		}

		/* Push non-cv qualifiers. */
		ddata->push_qualifier = PUSH_NON_CV_QUALIFIER;
		if (!cpp_demangle_push_type_qualifier(ddata, v, NULL))
			return (0);

		if (rc) {
			if (non_cv_qualifier && !DEM_PUSH_STR(ddata, " "))
				return (0);
			if ((class_type_size = ddata->class_type.size) == 0)
				return (0);
			class_type =
			    ddata->class_type.container[class_type_size - 1];
			if (class_type == NULL)
				return (0);
			if ((class_type_len = strlen(class_type)) == 0)
				return (0);
			if (!cpp_demangle_push_str(ddata, class_type,
			    class_type_len))
				return (0);
			if (!DEM_PUSH_STR(ddata, "::*"))
				return (0);
			/* Push pointer-to-member qualifiers. */
			ddata->push_qualifier = PUSH_ALL_QUALIFIER;
			if (!cpp_demangle_push_type_qualifier(ddata, rc->data,
			    NULL))
				return (0);
			++ddata->func_type;
		}

		if (paren) {
			if (!DEM_PUSH_STR(ddata, ")"))
				return (0);
			paren = false;
		}

		td.paren = false;
		td.firstp = true;
		limit = 0;
		ddata->is_functype = true;
		for (;;) {
			if (!cpp_demangle_read_type(ddata, &td))
				return (0);
			if (*ddata->cur == 'E')
				break;
			if (limit++ > CPP_DEMANGLE_TRY_LIMIT)
				return (0);
		}
		ddata->is_functype = false;
		if (td.paren) {
			if (!DEM_PUSH_STR(ddata, ")"))
				return (0);
			td.paren = false;
		}

		/* Push CV qualifiers. */
		ddata->push_qualifier = PUSH_CV_QUALIFIER;
		if (!cpp_demangle_push_type_qualifier(ddata, v, NULL))
			return (0);

		ddata->push_qualifier = PUSH_ALL_QUALIFIER;

		/* Release type qualifier vector. */
		vector_type_qualifier_dest(v);
		if (!vector_type_qualifier_init(v))
			return (0);

		/* Push ref-qualifiers. */
		if (ddata->ref_qualifier) {
			switch (ddata->ref_qualifier_type) {
			case TYPE_REF:
				if (!DEM_PUSH_STR(ddata, " &"))
					return (0);
				break;
			case TYPE_RREF:
				if (!DEM_PUSH_STR(ddata, " &&"))
					return (0);
				break;
			default:
				return (0);
			}
			ddata->ref_qualifier = false;
		}
	}

	++ddata->cur;

	return (1);
}