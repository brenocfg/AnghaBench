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
typedef  scalar_t__ u32 ;
struct context {int user; int role; int type; int /*<<< orphan*/  str; scalar_t__ len; } ;
struct TYPE_2__ {char** p_user_val_to_name; char** p_role_val_to_name; char** p_type_val_to_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mls_compute_context_len (struct context*) ; 
 int /*<<< orphan*/  mls_sid_to_context (struct context*,char**) ; 
 TYPE_1__ policydb ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int context_struct_to_string(struct context *context, char **scontext, u32 *scontext_len)
{
	char *scontextp;

	*scontext = NULL;
	*scontext_len = 0;

	if (context->len) {
		*scontext_len = context->len;
		*scontext = kstrdup(context->str, GFP_ATOMIC);
		if (!(*scontext))
			return -ENOMEM;
		return 0;
	}

	/* Compute the size of the context. */
	*scontext_len += strlen(policydb.p_user_val_to_name[context->user - 1]) + 1;
	*scontext_len += strlen(policydb.p_role_val_to_name[context->role - 1]) + 1;
	*scontext_len += strlen(policydb.p_type_val_to_name[context->type - 1]) + 1;
	*scontext_len += mls_compute_context_len(context);

	/* Allocate space for the context; caller must free this space. */
	scontextp = kmalloc(*scontext_len, GFP_ATOMIC);
	if (!scontextp)
		return -ENOMEM;
	*scontext = scontextp;

	/*
	 * Copy the user name, role name and type name into the context.
	 */
	sprintf(scontextp, "%s:%s:%s",
		policydb.p_user_val_to_name[context->user - 1],
		policydb.p_role_val_to_name[context->role - 1],
		policydb.p_type_val_to_name[context->type - 1]);
	scontextp += strlen(policydb.p_user_val_to_name[context->user - 1]) +
		     1 + strlen(policydb.p_role_val_to_name[context->role - 1]) +
		     1 + strlen(policydb.p_type_val_to_name[context->type - 1]);

	mls_sid_to_context(context, &scontextp);

	*scontextp = 0;

	return 0;
}