#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  thread_keyring; } ;

/* Variables and functions */
 TYPE_1__* id_resolver_cache ; 
 int /*<<< orphan*/  key_revoke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_id_resolver ; 
 int /*<<< orphan*/  put_cred (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_key_type (int /*<<< orphan*/ *) ; 

void nfs_idmap_quit(void)
{
	key_revoke(id_resolver_cache->thread_keyring);
	unregister_key_type(&key_type_id_resolver);
	put_cred(id_resolver_cache);
}