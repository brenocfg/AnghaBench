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
struct demangle_data {unsigned char* p; int cnst; int ptr; int ref; int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 scalar_t__ ELFTC_ISDIGIT (float) ; 
 int VEC_PUSH_STR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int read_array (struct demangle_data*) ; 
 int read_class (struct demangle_data*) ; 
 int read_func_ptr (struct demangle_data*) ; 
 int read_memptr (struct demangle_data*) ; 
 int read_qual_name (struct demangle_data*) ; 

__attribute__((used)) static bool
read_type(struct demangle_data *d)
{

	if (d == NULL)
		return (false);

	assert(d->p != NULL && "d->p (org str) is NULL");

	while (*d->p == 'U' || *d->p == 'C' || *d->p == 'V' || *d->p == 'S' ||
	       *d->p == 'P' || *d->p == 'R' || *d->p == 'A' || *d->p == 'F' ||
	       *d->p == 'M') {
		switch (*d->p) {
		case 'U' :
			++d->p;

			if (VEC_PUSH_STR(&d->vec, "unsigned ") == false)
				return (false);

			break;
		case 'C' :
			++d->p;

			if (*d->p == 'P')
				d->cnst = true;
			else {
				if (VEC_PUSH_STR(&d->vec, "const ") ==
				    false)
					return (false);
			}

			break;
		case 'V' :
			++d->p;

			if (VEC_PUSH_STR(&d->vec, "volatile ") == false)
				return (false);

			break;
		case 'S' :
			++d->p;

			if (VEC_PUSH_STR(&d->vec, "signed ") == false)
				return (false);

			break;
		case 'P' :
			++d->p;

			if (*d->p == 'F')
				return (read_func_ptr(d));
			else
				d->ptr = true;

			break;
		case 'R' :
			++d->p;

			d->ref = true;

			break;
		case 'F' :
			break;
		case 'A' :
			++d->p;

			if (read_array(d) == false)
				return (false);

			break;
		case 'M' :
			++d->p;

			if (read_memptr(d) == false)
				return (false);

			break;
		default :
			break;
		}
	}

	if (ELFTC_ISDIGIT(*d->p))
		return (read_class(d));

	switch (*d->p) {
	case 'Q' :
		++d->p;

		return (read_qual_name(d));
	case 'v' :
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "void"));
	case 'b':
		++d->p;

		return(VEC_PUSH_STR(&d->vec, "bool"));
	case 'c' :
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "char"));
	case 's' :
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "short"));
	case 'i' :
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "int"));
	case 'l' :
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "long"));
	case 'f' :
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "float"));
	case 'd':
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "double"));
	case 'r':
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "long double"));
	case 'e':
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "..."));
	case 'w':
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "wchar_t"));
	case 'x':
		++d->p;

		return (VEC_PUSH_STR(&d->vec, "long long"));
	default:
		return (false);
	};

	/* NOTREACHED */
	return (false);
}