#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  val; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Var ;
struct TYPE_10__ {int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  Hash_Entry ;
typedef  TYPE_2__ GNode ;

/* Variables and functions */
 char* ALLSRC ; 
 char* ARCHIVE ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *,int) ; 
 int FIND_CMD ; 
 int FIND_ENV ; 
 int FIND_GLOBAL ; 
 int /*<<< orphan*/ * Hash_FindEntry (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ Hash_GetValue (int /*<<< orphan*/ *) ; 
 char* IMPSRC ; 
 char* MEMBER ; 
 char* OODATE ; 
 char* PREFIX ; 
 char* TARGET ; 
 TYPE_2__* VAR_CMD ; 
 int /*<<< orphan*/  VAR_FROM_ENV ; 
 TYPE_2__* VAR_GLOBAL ; 
 TYPE_2__* VAR_INTERNAL ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char const*) ; 
 scalar_t__ checkEnvFirst ; 
 char* getenv (char const*) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static Var *
VarFind(const char *name, GNode *ctxt, int flags)
{
    Hash_Entry         	*var;
    Var			*v;

	/*
	 * If the variable name begins with a '.', it could very well be one of
	 * the local ones.  We check the name against all the local variables
	 * and substitute the short version in for 'name' if it matches one of
	 * them.
	 */
	if (*name == '.' && isupper((unsigned char) name[1]))
		switch (name[1]) {
		case 'A':
			if (!strcmp(name, ".ALLSRC"))
				name = ALLSRC;
			if (!strcmp(name, ".ARCHIVE"))
				name = ARCHIVE;
			break;
		case 'I':
			if (!strcmp(name, ".IMPSRC"))
				name = IMPSRC;
			break;
		case 'M':
			if (!strcmp(name, ".MEMBER"))
				name = MEMBER;
			break;
		case 'O':
			if (!strcmp(name, ".OODATE"))
				name = OODATE;
			break;
		case 'P':
			if (!strcmp(name, ".PREFIX"))
				name = PREFIX;
			break;
		case 'T':
			if (!strcmp(name, ".TARGET"))
				name = TARGET;
			break;
		}
#ifdef notyet
    /* for compatibility with gmake */
    if (name[0] == '^' && name[1] == '\0')
	    name = ALLSRC;
#endif

    /*
     * First look for the variable in the given context. If it's not there,
     * look for it in VAR_CMD, VAR_GLOBAL and the environment, in that order,
     * depending on the FIND_* flags in 'flags'
     */
    var = Hash_FindEntry(&ctxt->context, name);

    if ((var == NULL) && (flags & FIND_CMD) && (ctxt != VAR_CMD)) {
	var = Hash_FindEntry(&VAR_CMD->context, name);
    }
    if (!checkEnvFirst && (var == NULL) && (flags & FIND_GLOBAL) &&
	(ctxt != VAR_GLOBAL))
    {
	var = Hash_FindEntry(&VAR_GLOBAL->context, name);
	if ((var == NULL) && (ctxt != VAR_INTERNAL)) {
	    /* VAR_INTERNAL is subordinate to VAR_GLOBAL */
	    var = Hash_FindEntry(&VAR_INTERNAL->context, name);
	}
    }
    if ((var == NULL) && (flags & FIND_ENV)) {
	char *env;

	if ((env = getenv(name)) != NULL) {
	    int		len;

	    v = bmake_malloc(sizeof(Var));
	    v->name = bmake_strdup(name);

	    len = strlen(env);

	    Buf_Init(&v->val, len + 1);
	    Buf_AddBytes(&v->val, len, env);

	    v->flags = VAR_FROM_ENV;
	    return (v);
	} else if (checkEnvFirst && (flags & FIND_GLOBAL) &&
		   (ctxt != VAR_GLOBAL))
	{
	    var = Hash_FindEntry(&VAR_GLOBAL->context, name);
	    if ((var == NULL) && (ctxt != VAR_INTERNAL)) {
		var = Hash_FindEntry(&VAR_INTERNAL->context, name);
	    }
	    if (var == NULL) {
		return NULL;
	    } else {
		return ((Var *)Hash_GetValue(var));
	    }
	} else {
	    return NULL;
	}
    } else if (var == NULL) {
	return NULL;
    } else {
	return ((Var *)Hash_GetValue(var));
    }
}