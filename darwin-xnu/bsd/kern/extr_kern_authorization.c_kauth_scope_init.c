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

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_SCOPE_FILEOP ; 
 int /*<<< orphan*/  KAUTH_SCOPE_GENERIC ; 
 int /*<<< orphan*/  KAUTH_SCOPE_PROCESS ; 
 int /*<<< orphan*/ * kauth_authorize_generic_callback ; 
 int /*<<< orphan*/ * kauth_authorize_process_callback ; 
 int /*<<< orphan*/  kauth_lck_grp ; 
 void* kauth_register_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* kauth_scope_fileop ; 
 void* kauth_scope_generic ; 
 int /*<<< orphan*/  kauth_scope_mtx ; 
 void* kauth_scope_process ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kauth_scope_init(void)
{
	kauth_scope_mtx = lck_mtx_alloc_init(kauth_lck_grp, 0 /*LCK_ATTR_NULL*/);
	kauth_scope_process = kauth_register_scope(KAUTH_SCOPE_PROCESS, kauth_authorize_process_callback, NULL);
	kauth_scope_generic = kauth_register_scope(KAUTH_SCOPE_GENERIC, kauth_authorize_generic_callback, NULL);
	kauth_scope_fileop = kauth_register_scope(KAUTH_SCOPE_FILEOP, NULL, NULL);
}