#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* t_name; int t_id; struct TYPE_11__* t_tdesc; int /*<<< orphan*/  t_size; int /*<<< orphan*/  t_type; TYPE_1__* t_fndef; } ;
typedef  TYPE_2__ tdesc_t ;
typedef  int /*<<< orphan*/  fndef_t ;
struct TYPE_10__ {int /*<<< orphan*/  fn_ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY ; 
 int /*<<< orphan*/  CONST ; 
 int /*<<< orphan*/  FORWARD ; 
 int /*<<< orphan*/  FUNCTION ; 
 int /*<<< orphan*/  POINTER ; 
 int /*<<< orphan*/  RESTRICT ; 
 int /*<<< orphan*/  STRUCT ; 
 int /*<<< orphan*/  TYPEDEF ; 
 int /*<<< orphan*/  TYPEDEF_UNRES ; 
 int /*<<< orphan*/  TYPEFILE (int) ; 
 int /*<<< orphan*/  TYPENUM (int) ; 
 int /*<<< orphan*/  UNION ; 
 int /*<<< orphan*/  VOLATILE ; 
 int /*<<< orphan*/  addhash (TYPE_2__*,int) ; 
 char* arraydef (char*,TYPE_2__**) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  expected (char*,char*,char*) ; 
 int /*<<< orphan*/  faketypenumber ; 
 int /*<<< orphan*/  free (char*) ; 
 char* id (char*,int*) ; 
 char* intrinsic (char*,TYPE_2__**) ; 
 TYPE_2__* lookup (int) ; 
 int /*<<< orphan*/  lookupname (char*) ; 
 char* name (char*,char**) ; 
 int /*<<< orphan*/  parse_debug (int,char*,char*,...) ; 
 char* soudef (char*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  strchr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  terminate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 void* xcalloc (int) ; 

__attribute__((used)) static char *
tdefdecl(char *cp, int h, tdesc_t **rtdp)
{
	tdesc_t *ntdp;
	char *w;
	int c, h2;
	char type;

	parse_debug(3, cp, "tdefdecl h=%d", h);

	/* Type codes */
	switch (type = *cp) {
	case 'b': /* integer */
	case 'R': /* fp */
		cp = intrinsic(cp, rtdp);
		break;
	case '(': /* equiv to another type */
		cp = id(cp, &h2);
		ntdp = lookup(h2);

		if (ntdp != NULL && *cp == '=') {
			if (ntdp->t_type == FORWARD && *(cp + 1) == 'x') {
				/*
				 * The 6.2 compiler, and possibly others, will
				 * sometimes emit the same stab for a forward
				 * declaration twice.  That is, "(1,2)=xsfoo:"
				 * will sometimes show up in two different
				 * places.  This is, of course, quite fun.  We
				 * want CTF to work in spite of the compiler,
				 * so we'll let this one through.
				 */
				char *c2 = cp + 2;
				char *nm;

				if (!strchr("sue", *c2++)) {
					expected("tdefdecl/x-redefine", "[sue]",
					    c2 - 1);
				}

				c2 = name(c2, &nm);
				if (strcmp(nm, ntdp->t_name) != 0) {
					terminate("Stabs error: Attempt to "
					    "redefine type (%d,%d) as "
					    "something else: %s\n",
					    TYPEFILE(h2), TYPENUM(h2),
					    c2 - 1);
				}
				free(nm);

				h2 = faketypenumber++;
				ntdp = NULL;
			} else {
				terminate("Stabs error: Attempting to "
				    "redefine type (%d,%d)\n", TYPEFILE(h2),
				    TYPENUM(h2));
			}
		}

		if (ntdp == NULL) {  /* if that type isn't defined yet */
			if (*cp != '=') {
				/* record it as unresolved */
				parse_debug(3, NULL, "tdefdecl unres type %d",
				    h2);
				*rtdp = calloc(sizeof (**rtdp), 1);
				(*rtdp)->t_type = TYPEDEF_UNRES;
				(*rtdp)->t_id = h2;
				break;
			} else
				cp++;

			/* define a new type */
			cp = tdefdecl(cp, h2, rtdp);
			if ((*rtdp)->t_id && (*rtdp)->t_id != h2) {
				ntdp = calloc(sizeof (*ntdp), 1);
				ntdp->t_type = TYPEDEF;
				ntdp->t_tdesc = *rtdp;
				*rtdp = ntdp;
			}

			addhash(*rtdp, h2);

		} else { /* that type is already defined */
			if (ntdp->t_type != TYPEDEF || ntdp->t_name != NULL) {
				*rtdp = ntdp;
			} else {
				parse_debug(3, NULL,
				    "No duplicate typedef anon for ref");
				*rtdp = ntdp;
			}
		}
		break;
	case '*':
		ntdp = NULL;
		cp = tdefdecl(cp + 1, h, &ntdp);
		if (ntdp == NULL)
			expected("tdefdecl/*", "id", cp);

		if (!ntdp->t_id)
			ntdp->t_id = faketypenumber++;

		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_type = POINTER;
		(*rtdp)->t_size = 0;
		(*rtdp)->t_id = h;
		(*rtdp)->t_tdesc = ntdp;
		break;
	case 'f':
		cp = tdefdecl(cp + 1, h, &ntdp);
		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_type = FUNCTION;
		(*rtdp)->t_size = 0;
		(*rtdp)->t_id = h;
		(*rtdp)->t_fndef = xcalloc(sizeof (fndef_t));
		/*
		 * The 6.1 compiler will sometimes generate incorrect stabs for
		 * function pointers (it'll get the return type wrong).  This
		 * causes merges to fail.  We therefore treat function pointers
		 * as if they all point to functions that return int.  When
		 * 4432549 is fixed, the lookupname() call below should be
		 * replaced with `ntdp'.
		 */
		(*rtdp)->t_fndef->fn_ret = lookupname("int");
		break;
	case 'a':
	case 'z':
		cp++;
		if (*cp++ != 'r')
			expected("tdefdecl/[az]", "r", cp - 1);
		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_type = ARRAY;
		(*rtdp)->t_id = h;
		cp = arraydef(cp, rtdp);
		break;
	case 'x':
		c = *++cp;
		if (c != 's' && c != 'u' && c != 'e')
			expected("tdefdecl/x", "[sue]", cp - 1);
		cp = name(cp + 1, &w);

		ntdp = xcalloc(sizeof (*ntdp));
		ntdp->t_type = FORWARD;
		ntdp->t_name = w;
		/*
		 * We explicitly don't set t_id here - the caller will do it.
		 * The caller may want to use a real type ID, or they may
		 * choose to make one up.
		 */

		*rtdp = ntdp;
		break;

	case 'B': /* volatile */
		cp = tdefdecl(cp + 1, h, &ntdp);

		if (!ntdp->t_id)
			ntdp->t_id = faketypenumber++;

		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_type = VOLATILE;
		(*rtdp)->t_size = 0;
		(*rtdp)->t_tdesc = ntdp;
		(*rtdp)->t_id = h;
		break;

	case 'k': /* const */
		cp = tdefdecl(cp + 1, h, &ntdp);

		if (!ntdp->t_id)
			ntdp->t_id = faketypenumber++;

		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_type = CONST;
		(*rtdp)->t_size = 0;
		(*rtdp)->t_tdesc = ntdp;
		(*rtdp)->t_id = h;
		break;

	case 'K': /* restricted */
		cp = tdefdecl(cp + 1, h, &ntdp);

		if (!ntdp->t_id)
			ntdp->t_id = faketypenumber++;

		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_type = RESTRICT;
		(*rtdp)->t_size = 0;
		(*rtdp)->t_tdesc = ntdp;
		(*rtdp)->t_id = h;
		break;

	case 'u':
	case 's':
		cp++;

		*rtdp = xcalloc(sizeof (**rtdp));
		(*rtdp)->t_name = NULL;
		cp = soudef(cp, (type == 'u') ? UNION : STRUCT, rtdp);
		break;
	default:
		expected("tdefdecl", "<type code>", cp);
	}
	return (cp);
}