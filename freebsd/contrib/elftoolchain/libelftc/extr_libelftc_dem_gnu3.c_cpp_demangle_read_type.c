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
struct vector_str {size_t size; } ;
struct vector_type_qualifier {struct vector_str ext_name; } ;
struct type_delimit {int paren; int firstp; } ;
struct TYPE_2__ {int size; } ;
struct cpp_demangle_data {char* cur; int ref_qualifier; struct vector_str subst; void* ref_qualifier_type; int /*<<< orphan*/  is_functype; TYPE_1__ output; struct vector_str* cur_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 void* TYPE_CMX ; 
 void* TYPE_CST ; 
 void* TYPE_EXT ; 
 void* TYPE_IMG ; 
 void* TYPE_PTR ; 
 void* TYPE_REF ; 
 void* TYPE_RREF ; 
 void* TYPE_RST ; 
 void* TYPE_VAT ; 
 void* TYPE_VEC ; 
 int /*<<< orphan*/  VEC_PUSH_STR (struct vector_str*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_demangle_pop_str (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_push_subst_v (struct cpp_demangle_data*,struct vector_str*) ; 
 int /*<<< orphan*/  cpp_demangle_push_type_qualifier (struct cpp_demangle_data*,struct vector_type_qualifier*,char*) ; 
 int /*<<< orphan*/  cpp_demangle_read_array (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_expression_flat (struct cpp_demangle_data*,char**) ; 
 int /*<<< orphan*/  cpp_demangle_read_function (struct cpp_demangle_data*,int*,struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  cpp_demangle_read_name (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_number (struct cpp_demangle_data*,long*) ; 
 int /*<<< orphan*/  cpp_demangle_read_number_as_string (struct cpp_demangle_data*,char**) ; 
 int /*<<< orphan*/  cpp_demangle_read_pointer_to_member (struct cpp_demangle_data*,struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  cpp_demangle_read_sname (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_subst (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_args (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_param (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_find (struct vector_str*,char*,size_t) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_push (struct vector_str*,char*,size_t) ; 
 char* vector_str_substr (struct vector_str*,size_t,int,size_t*) ; 
 int /*<<< orphan*/  vector_type_qualifier_dest (struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_type_qualifier_init (struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_type_qualifier_push (struct vector_type_qualifier*,void*) ; 

__attribute__((used)) static int
cpp_demangle_read_type(struct cpp_demangle_data *ddata,
    struct type_delimit *td)
{
	struct vector_type_qualifier v;
	struct vector_str *output, sv;
	size_t p_idx, type_str_len, subst_str_len;
	int extern_c, is_builtin;
	long len;
	const char *p;
	char *type_str, *exp_str, *num_str, *subst_str;
	bool skip_ref_qualifier, omit_void;

	if (ddata == NULL)
		return (0);

	output = ddata->cur_output;
	if (td) {
		if (td->paren == false) {
			if (!DEM_PUSH_STR(ddata, "("))
				return (0);
			if (ddata->output.size < 2)
				return (0);
			td->paren = true;
		}

		if (!td->firstp) {
			if (*ddata->cur != 'I') {
				if (!DEM_PUSH_STR(ddata, ", "))
					return (0);
			}
		}
	}

	assert(output != NULL);
	/*
	 * [r, V, K] [P, R, O, C, G, U] builtin, function, class-enum, array
	 * pointer-to-member, template-param, template-template-param, subst
	 */

	if (!vector_type_qualifier_init(&v))
		return (0);

	extern_c = 0;
	is_builtin = 1;
	p_idx = output->size;
	type_str = exp_str = num_str = NULL;
	skip_ref_qualifier = false;

again:

	/* Clear ref-qualifier flag */
	if (*ddata->cur != 'R' && *ddata->cur != 'O' && *ddata->cur != 'E')
		ddata->ref_qualifier = false;

	/* builtin type */
	switch (*ddata->cur) {
	case 'a':
		/* signed char */
		if (!DEM_PUSH_STR(ddata, "signed char"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'A':
		/* array type */
		if (!cpp_demangle_read_array(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'b':
		/* bool */
		if (!DEM_PUSH_STR(ddata, "bool"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'C':
		/* complex pair */
		if (!vector_type_qualifier_push(&v, TYPE_CMX))
			goto clean;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'c':
		/* char */
		if (!DEM_PUSH_STR(ddata, "char"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'd':
		/* double */
		if (!DEM_PUSH_STR(ddata, "double"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'D':
		++ddata->cur;
		switch (*ddata->cur) {
		case 'a':
			/* auto */
			if (!DEM_PUSH_STR(ddata, "auto"))
				goto clean;
			++ddata->cur;
			break;
		case 'c':
			/* decltype(auto) */
			if (!DEM_PUSH_STR(ddata, "decltype(auto)"))
				goto clean;
			++ddata->cur;
			break;
		case 'd':
			/* IEEE 754r decimal floating point (64 bits) */
			if (!DEM_PUSH_STR(ddata, "decimal64"))
				goto clean;
			++ddata->cur;
			break;
		case 'e':
			/* IEEE 754r decimal floating point (128 bits) */
			if (!DEM_PUSH_STR(ddata, "decimal128"))
				goto clean;
			++ddata->cur;
			break;
		case 'f':
			/* IEEE 754r decimal floating point (32 bits) */
			if (!DEM_PUSH_STR(ddata, "decimal32"))
				goto clean;
			++ddata->cur;
			break;
		case 'h':
			/* IEEE 754r half-precision floating point (16 bits) */
			if (!DEM_PUSH_STR(ddata, "half"))
				goto clean;
			++ddata->cur;
			break;
		case 'i':
			/* char32_t */
			if (!DEM_PUSH_STR(ddata, "char32_t"))
				goto clean;
			++ddata->cur;
			break;
		case 'n':
			/* std::nullptr_t (i.e., decltype(nullptr)) */
			if (!DEM_PUSH_STR(ddata, "decltype(nullptr)"))
				goto clean;
			++ddata->cur;
			break;
		case 's':
			/* char16_t */
			if (!DEM_PUSH_STR(ddata, "char16_t"))
				goto clean;
			++ddata->cur;
			break;
		case 'v':
			/* gcc vector_size extension. */
			++ddata->cur;
			if (*ddata->cur == '_') {
				++ddata->cur;
				if (!cpp_demangle_read_expression_flat(ddata,
				    &exp_str))
					goto clean;
				if (!VEC_PUSH_STR(&v.ext_name, exp_str))
					goto clean;
			} else {
				if (!cpp_demangle_read_number_as_string(ddata,
				    &num_str))
					goto clean;
				if (!VEC_PUSH_STR(&v.ext_name, num_str))
					goto clean;
			}
			if (*ddata->cur != '_')
				goto clean;
			++ddata->cur;
			if (!vector_type_qualifier_push(&v, TYPE_VEC))
				goto clean;
			if (td)
				td->firstp = false;
			goto again;
		default:
			goto clean;
		}
		goto rtn;

	case 'e':
		/* long double */
		if (!DEM_PUSH_STR(ddata, "long double"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'E':
		/* unexpected end except ref-qualifiers */
		if (ddata->ref_qualifier && ddata->is_functype) {
			skip_ref_qualifier = true;
			/* Pop the delimiter. */
			cpp_demangle_pop_str(ddata);
			goto rtn;
		}
		goto clean;

	case 'f':
		/* float */
		if (!DEM_PUSH_STR(ddata, "float"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'F':
		/* function */
		if (!cpp_demangle_read_function(ddata, &extern_c, &v))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'g':
		/* __float128 */
		if (!DEM_PUSH_STR(ddata, "__float128"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'G':
		/* imaginary */
		if (!vector_type_qualifier_push(&v, TYPE_IMG))
			goto clean;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'h':
		/* unsigned char */
		if (!DEM_PUSH_STR(ddata, "unsigned char"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'i':
		/* int */
		if (!DEM_PUSH_STR(ddata, "int"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'I':
		/* template args. */
		/* handles <substitute><template-args> */
		p_idx = output->size;
		if (!cpp_demangle_read_tmpl_args(ddata))
			goto clean;
		if ((subst_str = vector_str_substr(output, p_idx,
		    output->size - 1, &subst_str_len)) == NULL)
			goto clean;
		if (!vector_str_init(&sv)) {
			free(subst_str);
			goto clean;
		}
		if (!vector_str_push(&sv, subst_str, subst_str_len)) {
			free(subst_str);
			vector_str_dest(&sv);
			goto clean;
		}
		free(subst_str);
		if (!cpp_demangle_push_subst_v(ddata, &sv)) {
			vector_str_dest(&sv);
			goto clean;
		}
		vector_str_dest(&sv);
		goto rtn;

	case 'j':
		/* unsigned int */
		if (!DEM_PUSH_STR(ddata, "unsigned int"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'K':
		/* const */
		if (!vector_type_qualifier_push(&v, TYPE_CST))
			goto clean;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'l':
		/* long */
		if (!DEM_PUSH_STR(ddata, "long"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'm':
		/* unsigned long */
		if (!DEM_PUSH_STR(ddata, "unsigned long"))
			goto clean;

		++ddata->cur;

		goto rtn;
	case 'M':
		/* pointer to member */
		if (!cpp_demangle_read_pointer_to_member(ddata, &v))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'n':
		/* __int128 */
		if (!DEM_PUSH_STR(ddata, "__int128"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'o':
		/* unsigned __int128 */
		if (!DEM_PUSH_STR(ddata, "unsigned __int128"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'O':
		/* rvalue reference */
		if (ddata->ref_qualifier)
			goto clean;
		if (!vector_type_qualifier_push(&v, TYPE_RREF))
			goto clean;
		ddata->ref_qualifier = true;
		ddata->ref_qualifier_type = TYPE_RREF;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'P':
		/* pointer */
		if (!vector_type_qualifier_push(&v, TYPE_PTR))
			goto clean;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'r':
		/* restrict */
		if (!vector_type_qualifier_push(&v, TYPE_RST))
			goto clean;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'R':
		/* reference */
		if (ddata->ref_qualifier)
			goto clean;
		if (!vector_type_qualifier_push(&v, TYPE_REF))
			goto clean;
		ddata->ref_qualifier = true;
		ddata->ref_qualifier_type = TYPE_REF;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 's':
		/* short, local string */
		if (!DEM_PUSH_STR(ddata, "short"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'S':
		/* substitution */
		if (!cpp_demangle_read_subst(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 't':
		/* unsigned short */
		if (!DEM_PUSH_STR(ddata, "unsigned short"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'T':
		/* template parameter */
		if (!cpp_demangle_read_tmpl_param(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'u':
		/* vendor extended builtin */
		++ddata->cur;
		if (!cpp_demangle_read_sname(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'U':
		/* vendor extended type qualifier */
		++ddata->cur;
		if (!cpp_demangle_read_number(ddata, &len))
			goto clean;
		if (len <= 0)
			goto clean;
		if (!vector_str_push(&v.ext_name, ddata->cur, len))
			return (0);
		ddata->cur += len;
		if (!vector_type_qualifier_push(&v, TYPE_EXT))
			goto clean;
		if (td)
			td->firstp = false;
		goto again;

	case 'v':
		/* void */
		omit_void = false;
		if (td && td->firstp) {
			/*
			 * peek into next bytes and see if we should omit
			 * the "void".
			 */
			omit_void = true;
			for (p = ddata->cur + 1; *p != '\0'; p++) {
				if (*p == 'E')
					break;
				if (*p != 'R' && *p != 'O') {
					omit_void = false;
					break;
				}
			}
		}
		if (!omit_void && !DEM_PUSH_STR(ddata, "void"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'V':
		/* volatile */
		if (!vector_type_qualifier_push(&v, TYPE_VAT))
			goto clean;
		++ddata->cur;
		if (td)
			td->firstp = false;
		goto again;

	case 'w':
		/* wchar_t */
		if (!DEM_PUSH_STR(ddata, "wchar_t"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'x':
		/* long long */
		if (!DEM_PUSH_STR(ddata, "long long"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'y':
		/* unsigned long long */
		if (!DEM_PUSH_STR(ddata, "unsigned long long"))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'z':
		/* ellipsis */
		if (!DEM_PUSH_STR(ddata, "..."))
			goto clean;
		++ddata->cur;
		goto rtn;
	}

	if (!cpp_demangle_read_name(ddata))
		goto clean;

	is_builtin = 0;
rtn:

	type_str = vector_str_substr(output, p_idx, output->size - 1,
	    &type_str_len);

	if (is_builtin == 0) {
		if (!vector_str_find(&ddata->subst, type_str, type_str_len) &&
		    !vector_str_push(&ddata->subst, type_str, type_str_len))
			goto clean;
	}

	if (!skip_ref_qualifier &&
	    !cpp_demangle_push_type_qualifier(ddata, &v, type_str))
		goto clean;

	if (td)
		td->firstp = false;

	free(type_str);
	free(exp_str);
	free(num_str);
	vector_type_qualifier_dest(&v);

	return (1);
clean:
	free(type_str);
	free(exp_str);
	free(num_str);
	vector_type_qualifier_dest(&v);

	return (0);
}