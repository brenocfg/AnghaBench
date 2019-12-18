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
struct sctp_shared_key {int dummy; } ;
struct sctp_auth_bytes {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  auth_capable; } ;
struct sctp_association {struct sctp_auth_bytes* asoc_shared_key; int /*<<< orphan*/  active_key_id; TYPE_1__ peer; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct sctp_auth_bytes* sctp_auth_asoc_create_secret (struct sctp_association*,struct sctp_shared_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_enable ; 
 struct sctp_shared_key* sctp_auth_get_shkey (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_key_put (struct sctp_auth_bytes*) ; 

int sctp_auth_asoc_init_active_key(struct sctp_association *asoc, gfp_t gfp)
{
	struct sctp_auth_bytes	*secret;
	struct sctp_shared_key *ep_key;

	/* If we don't support AUTH, or peer is not capable
	 * we don't need to do anything.
	 */
	if (!sctp_auth_enable || !asoc->peer.auth_capable)
		return 0;

	/* If the key_id is non-zero and we couldn't find an
	 * endpoint pair shared key, we can't compute the
	 * secret.
	 * For key_id 0, endpoint pair shared key is a NULL key.
	 */
	ep_key = sctp_auth_get_shkey(asoc, asoc->active_key_id);
	BUG_ON(!ep_key);

	secret = sctp_auth_asoc_create_secret(asoc, ep_key, gfp);
	if (!secret)
		return -ENOMEM;

	sctp_auth_key_put(asoc->asoc_shared_key);
	asoc->asoc_shared_key = secret;

	return 0;
}