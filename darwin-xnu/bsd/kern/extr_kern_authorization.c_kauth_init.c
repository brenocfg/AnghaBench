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
typedef  int /*<<< orphan*/  lck_grp_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_cred_init () ; 
 int /*<<< orphan*/  kauth_dangling_listeners ; 
 int /*<<< orphan*/  kauth_groups_init () ; 
 int /*<<< orphan*/  kauth_identity_init () ; 
 int /*<<< orphan*/ * kauth_lck_grp ; 
 int /*<<< orphan*/  kauth_resolver_init () ; 
 int /*<<< orphan*/  kauth_scope_init () ; 
 int /*<<< orphan*/  kauth_scopes ; 
 int /*<<< orphan*/ * lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_free (int /*<<< orphan*/ *) ; 

void
kauth_init(void)
{
	lck_grp_attr_t	*grp_attributes;

	TAILQ_INIT(&kauth_scopes);
	TAILQ_INIT(&kauth_dangling_listeners);

	/* set up our lock group */
	grp_attributes = lck_grp_attr_alloc_init();
	kauth_lck_grp = lck_grp_alloc_init("kauth", grp_attributes);
	lck_grp_attr_free(grp_attributes);

	/* bring up kauth subsystem components */
	kauth_cred_init();
#if CONFIG_EXT_RESOLVER
	kauth_identity_init();
	kauth_groups_init();
#endif
	kauth_scope_init();
#if CONFIG_EXT_RESOLVER
	kauth_resolver_init();
#endif
	/* can't alloc locks after this */
	lck_grp_free(kauth_lck_grp);
	kauth_lck_grp = NULL;
}