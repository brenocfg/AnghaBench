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
typedef  size_t u_long ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_CRED_HASH_LOCK_ASSERT () ; 
 size_t KAUTH_CRED_TABLE_SIZE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr_link ; 
 int /*<<< orphan*/ * kauth_cred_find (int /*<<< orphan*/ ) ; 
 size_t kauth_cred_get_hashkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kauth_cred_table_anchor ; 

__attribute__((used)) static int
kauth_cred_add(kauth_cred_t new_cred)
{
	u_long			hash_key;

	KAUTH_CRED_HASH_LOCK_ASSERT();

	hash_key = kauth_cred_get_hashkey(new_cred);
	hash_key %= KAUTH_CRED_TABLE_SIZE;

	/* race fix - there is a window where another matching credential 
	 * could have been inserted between the time this one was created and we
	 * got the hash lock.  If we find a match return an error and have the 
	 * the caller retry.
	 */
	if (kauth_cred_find(new_cred) != NULL) {
		return(-1);
	}
	
	/* take a reference for our use in credential hash table */ 
	kauth_cred_ref(new_cred);

	/* insert the credential into the hash table */
	TAILQ_INSERT_HEAD(&kauth_cred_table_anchor[hash_key], new_cred, cr_link);
	
	return(0);
}