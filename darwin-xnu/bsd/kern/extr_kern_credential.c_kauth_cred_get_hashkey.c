#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_long ;
struct posix_cred {int dummy; } ;
struct label {int dummy; } ;
struct au_session {int dummy; } ;
typedef  TYPE_1__* posix_cred_t ;
typedef  TYPE_2__* kauth_cred_t ;
struct TYPE_7__ {scalar_t__ cr_label; int /*<<< orphan*/  cr_audit; int /*<<< orphan*/  cr_posix; } ;
struct TYPE_6__ {int cr_flags; } ;

/* Variables and functions */
 int CRF_MAC_ENFORCE ; 
 int /*<<< orphan*/  kauth_cred_hash (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* posix_cred_get (TYPE_2__*) ; 

__attribute__((used)) static u_long
kauth_cred_get_hashkey(kauth_cred_t cred)
{
#if CONFIG_MACF
	posix_cred_t pcred = posix_cred_get(cred);
#endif
	u_long	hash_key = 0;

	hash_key = kauth_cred_hash((uint8_t *)&cred->cr_posix, 
							   sizeof (struct posix_cred),
							   hash_key);
	hash_key = kauth_cred_hash((uint8_t *)&cred->cr_audit, 
							   sizeof(struct au_session),
							   hash_key);
#if CONFIG_MACF
	if (pcred->cr_flags & CRF_MAC_ENFORCE) {
		hash_key = kauth_cred_hash((uint8_t *)cred->cr_label, 
								   sizeof (struct label),
								   hash_key);
	}
#endif
	return(hash_key);
}