#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sctp_hmac {unsigned int hmac_len; } ;
struct sctp_endpoint {int dummy; } ;
struct TYPE_5__ {struct sctp_authhdr* auth_hdr; } ;
struct sctp_chunk {int auth; TYPE_2__* chunk_hdr; TYPE_3__* skb; TYPE_1__ subh; } ;
struct sctp_authhdr {int /*<<< orphan*/ * hmac; int /*<<< orphan*/  hmac_id; int /*<<< orphan*/  shkey_id; } ;
struct sctp_auth_chunk {int dummy; } ;
struct sctp_association {scalar_t__ active_key_id; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_ierror_t ;
typedef  int /*<<< orphan*/  sctp_auth_chunk_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u16 ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_IERROR_AUTH_BAD_HMAC ; 
 int /*<<< orphan*/  SCTP_IERROR_AUTH_BAD_KEYID ; 
 int /*<<< orphan*/  SCTP_IERROR_BAD_SIG ; 
 int /*<<< orphan*/  SCTP_IERROR_NOMEM ; 
 int /*<<< orphan*/  SCTP_IERROR_NO_ERROR ; 
 int /*<<< orphan*/  SCTP_IERROR_PROTO_VIOLATION ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_asoc_verify_hmac_id (struct sctp_association const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_calculate_hmac (struct sctp_association const*,TYPE_3__*,struct sctp_auth_chunk*,int /*<<< orphan*/ ) ; 
 struct sctp_hmac* sctp_auth_get_hmac (scalar_t__) ; 
 int /*<<< orphan*/  sctp_auth_get_shkey (struct sctp_association const*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static sctp_ierror_t sctp_sf_authenticate(const struct sctp_endpoint *ep,
				    const struct sctp_association *asoc,
				    const sctp_subtype_t type,
				    struct sctp_chunk *chunk)
{
	struct sctp_authhdr *auth_hdr;
	struct sctp_hmac *hmac;
	unsigned int sig_len;
	__u16 key_id;
	__u8 *save_digest;
	__u8 *digest;

	/* Pull in the auth header, so we can do some more verification */
	auth_hdr = (struct sctp_authhdr *)chunk->skb->data;
	chunk->subh.auth_hdr = auth_hdr;
	skb_pull(chunk->skb, sizeof(struct sctp_authhdr));

	/* Make sure that we suport the HMAC algorithm from the auth
	 * chunk.
	 */
	if (!sctp_auth_asoc_verify_hmac_id(asoc, auth_hdr->hmac_id))
		return SCTP_IERROR_AUTH_BAD_HMAC;

	/* Make sure that the provided shared key identifier has been
	 * configured
	 */
	key_id = ntohs(auth_hdr->shkey_id);
	if (key_id != asoc->active_key_id && !sctp_auth_get_shkey(asoc, key_id))
		return SCTP_IERROR_AUTH_BAD_KEYID;


	/* Make sure that the length of the signature matches what
	 * we expect.
	 */
	sig_len = ntohs(chunk->chunk_hdr->length) - sizeof(sctp_auth_chunk_t);
	hmac = sctp_auth_get_hmac(ntohs(auth_hdr->hmac_id));
	if (sig_len != hmac->hmac_len)
		return SCTP_IERROR_PROTO_VIOLATION;

	/* Now that we've done validation checks, we can compute and
	 * verify the hmac.  The steps involved are:
	 *  1. Save the digest from the chunk.
	 *  2. Zero out the digest in the chunk.
	 *  3. Compute the new digest
	 *  4. Compare saved and new digests.
	 */
	digest = auth_hdr->hmac;
	skb_pull(chunk->skb, sig_len);

	save_digest = kmemdup(digest, sig_len, GFP_ATOMIC);
	if (!save_digest)
		goto nomem;

	memset(digest, 0, sig_len);

	sctp_auth_calculate_hmac(asoc, chunk->skb,
				(struct sctp_auth_chunk *)chunk->chunk_hdr,
				GFP_ATOMIC);

	/* Discard the packet if the digests do not match */
	if (memcmp(save_digest, digest, sig_len)) {
		kfree(save_digest);
		return SCTP_IERROR_BAD_SIG;
	}

	kfree(save_digest);
	chunk->auth = 1;

	return SCTP_IERROR_NO_ERROR;
nomem:
	return SCTP_IERROR_NOMEM;
}