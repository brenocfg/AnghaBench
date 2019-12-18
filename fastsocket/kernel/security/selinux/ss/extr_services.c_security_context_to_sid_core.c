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
typedef  int u32 ;
struct context {char* str; int len; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int SECINITSID_KERNEL ; 
 int SECINITSID_NUM ; 
 int SECSID_NULL ; 
 int /*<<< orphan*/  context_destroy (struct context*) ; 
 int /*<<< orphan*/ * initial_sid_to_string ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  policy_rwlock ; 
 int /*<<< orphan*/  policydb ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sidtab ; 
 int sidtab_context_to_sid (int /*<<< orphan*/ *,struct context*,int*) ; 
 int /*<<< orphan*/  ss_initialized ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int string_to_context_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,struct context*,int) ; 

__attribute__((used)) static int security_context_to_sid_core(const char *scontext, u32 scontext_len,
					u32 *sid, u32 def_sid, gfp_t gfp_flags,
					int force)
{
	char *scontext2, *str = NULL;
	struct context context;
	int rc = 0;

	if (!ss_initialized) {
		int i;

		for (i = 1; i < SECINITSID_NUM; i++) {
			if (!strcmp(initial_sid_to_string[i], scontext)) {
				*sid = i;
				return 0;
			}
		}
		*sid = SECINITSID_KERNEL;
		return 0;
	}
	*sid = SECSID_NULL;

	/* Copy the string so that we can modify the copy as we parse it. */
	scontext2 = kmalloc(scontext_len+1, gfp_flags);
	if (!scontext2)
		return -ENOMEM;
	memcpy(scontext2, scontext, scontext_len);
	scontext2[scontext_len] = 0;

	if (force) {
		/* Save another copy for storing in uninterpreted form */
		str = kstrdup(scontext2, gfp_flags);
		if (!str) {
			kfree(scontext2);
			return -ENOMEM;
		}
	}

	read_lock(&policy_rwlock);
	rc = string_to_context_struct(&policydb, &sidtab,
				      scontext2, scontext_len,
				      &context, def_sid);
	if (rc == -EINVAL && force) {
		context.str = str;
		context.len = scontext_len;
		str = NULL;
	} else if (rc)
		goto out;
	rc = sidtab_context_to_sid(&sidtab, &context, sid);
	context_destroy(&context);
out:
	read_unlock(&policy_rwlock);
	kfree(scontext2);
	kfree(str);
	return rc;
}