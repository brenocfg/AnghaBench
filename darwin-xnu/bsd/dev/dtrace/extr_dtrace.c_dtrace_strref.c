#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* dtst_str; int dtst_refcount; } ;
typedef  TYPE_1__ dtrace_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__** DTRACE_HASHNEXT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  dtrace_hash_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* dtrace_hash_lookup_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_strings ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static char *
dtrace_strref(const char *str)
{
	dtrace_string_t *s = NULL;
	size_t bufsize = (str != NULL ? strlen(str) : 0) + 1;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	if (str == NULL)
		str = "";

	for (s = dtrace_hash_lookup_string(dtrace_strings, str); s != NULL;
	     s = *(DTRACE_HASHNEXT(dtrace_strings, s)))  {
		if (strncmp(str, s->dtst_str, bufsize) != 0) {
			continue;
		}
		ASSERT(s->dtst_refcount != UINT32_MAX);
		s->dtst_refcount++;
		return s->dtst_str;
	}

	s = kmem_zalloc(sizeof(dtrace_string_t) + bufsize, KM_SLEEP);
	s->dtst_refcount = 1;
	(void) strlcpy(s->dtst_str, str, bufsize);

	dtrace_hash_add(dtrace_strings, s);

	return s->dtst_str;
}