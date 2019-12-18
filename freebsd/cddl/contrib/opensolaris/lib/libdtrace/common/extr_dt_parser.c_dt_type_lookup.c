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
typedef  int /*<<< orphan*/  dtrace_typeinfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_2__ {scalar_t__ pcb_idepth; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 char* DTRACE_OBJ_CDEFS ; 
 char* DTRACE_OBJ_EVERY ; 
 int /*<<< orphan*/  EDT_BADSCOPE ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dtrace_lookup_by_type (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char const) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* strpbrk (char const*,char const*) ; 
 TYPE_1__* yypcb ; 

int
dt_type_lookup(const char *s, dtrace_typeinfo_t *tip)
{
	static const char delimiters[] = " \t\n\r\v\f*`";
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	const char *p, *q, *r, *end, *obj;

	for (p = s, end = s + strlen(s); *p != '\0'; p = q) {
		while (isspace(*p))
			p++;	/* skip leading whitespace prior to token */

		if (p == end || (q = strpbrk(p + 1, delimiters)) == NULL)
			break;	/* empty string or single token remaining */

		if (*q == '`') {
			char *object = alloca((size_t)(q - p) + 1);
			char *type = alloca((size_t)(end - s) + 1);

			/*
			 * Copy from the start of the token (p) to the location
			 * backquote (q) to extract the nul-terminated object.
			 */
			bcopy(p, object, (size_t)(q - p));
			object[(size_t)(q - p)] = '\0';

			/*
			 * Copy the original string up to the start of this
			 * token (p) into type, and then concatenate everything
			 * after q.  This is the type name without the object.
			 */
			bcopy(s, type, (size_t)(p - s));
			bcopy(q + 1, type + (size_t)(p - s), strlen(q + 1) + 1);

			/*
			 * There may be at most three delimeters. The second
			 * delimeter is usually used to distinguish the type
			 * within a given module, however, there could be a link
			 * map id on the scene in which case that delimeter
			 * would be the third. We determine presence of the lmid
			 * if it rouglhly meets the from LM[0-9]
			 */
			if ((r = strchr(q + 1, '`')) != NULL &&
			    ((r = strchr(r + 1, '`')) != NULL)) {
				if (strchr(r + 1, '`') != NULL)
					return (dt_set_errno(dtp,
					    EDT_BADSCOPE));
				if (q[1] != 'L' || q[2] != 'M')
					return (dt_set_errno(dtp,
					    EDT_BADSCOPE));
			}

			return (dtrace_lookup_by_type(dtp, object, type, tip));
		}
	}

	if (yypcb->pcb_idepth != 0)
		obj = DTRACE_OBJ_CDEFS;
	else
		obj = DTRACE_OBJ_EVERY;

	return (dtrace_lookup_by_type(dtp, obj, s, tip));
}