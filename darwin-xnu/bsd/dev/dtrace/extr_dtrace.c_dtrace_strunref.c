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
struct TYPE_7__ {scalar_t__ dtst_refcount; int /*<<< orphan*/  dtst_str; } ;
typedef  TYPE_1__ dtrace_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__** DTRACE_HASHNEXT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 TYPE_1__* dtrace_hash_lookup_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dtrace_hash_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_strings ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  panic (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
dtrace_strunref(const char *str)
{
	ASSERT(str != NULL);
	dtrace_string_t *s = NULL;
	size_t bufsize = strlen(str) + 1;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	for (s = dtrace_hash_lookup_string(dtrace_strings, str); s != NULL;
	     s = *(DTRACE_HASHNEXT(dtrace_strings, s)))  {
		if (strncmp(str, s->dtst_str, bufsize) != 0) {
			continue;
		}
		ASSERT(s->dtst_refcount != 0);
		s->dtst_refcount--;
		if (s->dtst_refcount == 0) {
			dtrace_hash_remove(dtrace_strings, s);
			kmem_free(s, sizeof(dtrace_string_t) + bufsize);
		}
		return;
	}
	panic("attempt to unref non-existent string %s", str);
}