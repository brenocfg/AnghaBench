#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sctp_hmac {scalar_t__ hmac_len; scalar_t__ hmac_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  auth_hdr; } ;
struct sctp_chunk {int /*<<< orphan*/  skb; int /*<<< orphan*/  chunk_end; TYPE_2__* chunk_hdr; TYPE_1__ subh; } ;
struct sctp_authhdr {void* shkey_id; void* hmac_id; } ;
struct sctp_association {scalar_t__ active_key_id; } ;
typedef  int /*<<< orphan*/  sctp_authhdr_t ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {void* length; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_AUTH ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ntohs (void*) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_authhdr*) ; 
 struct sctp_hmac* sctp_auth_asoc_get_hmac (struct sctp_association const*) ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * skb_put (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_tail_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sctp_chunk *sctp_make_auth(const struct sctp_association *asoc)
{
	struct sctp_chunk *retval;
	struct sctp_hmac *hmac_desc;
	struct sctp_authhdr auth_hdr;
	__u8 *hmac;

	/* Get the first hmac that the peer told us to use */
	hmac_desc = sctp_auth_asoc_get_hmac(asoc);
	if (unlikely(!hmac_desc))
		return NULL;

	retval = sctp_make_chunk(asoc, SCTP_CID_AUTH, 0,
			hmac_desc->hmac_len + sizeof(sctp_authhdr_t));
	if (!retval)
		return NULL;

	auth_hdr.hmac_id = htons(hmac_desc->hmac_id);
	auth_hdr.shkey_id = htons(asoc->active_key_id);

	retval->subh.auth_hdr = sctp_addto_chunk(retval, sizeof(sctp_authhdr_t),
						&auth_hdr);

	hmac = skb_put(retval->skb, hmac_desc->hmac_len);
	memset(hmac, 0, hmac_desc->hmac_len);

	/* Adjust the chunk header to include the empty MAC */
	retval->chunk_hdr->length =
		htons(ntohs(retval->chunk_hdr->length) + hmac_desc->hmac_len);
	retval->chunk_end = skb_tail_pointer(retval->skb);

	return retval;
}