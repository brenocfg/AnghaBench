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
struct nfsd4_create_session {int dummy; } ;
struct nfsd4_clid_slot {int sl_status; int /*<<< orphan*/  sl_cr_ses; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nfsd4_create_session*,int) ; 

__attribute__((used)) static void
nfsd4_cache_create_session(struct nfsd4_create_session *cr_ses,
			   struct nfsd4_clid_slot *slot, int nfserr)
{
	slot->sl_status = nfserr;
	memcpy(&slot->sl_cr_ses, cr_ses, sizeof(*cr_ses));
}