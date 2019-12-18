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
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct sctp_hmac_algo_param {int /*<<< orphan*/  hmac_ids; TYPE_2__ param_hdr; } ;
struct TYPE_3__ {scalar_t__ auth_hmacs; } ;
struct sctp_association {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int __sctp_auth_find_hmacid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

int sctp_auth_asoc_verify_hmac_id(const struct sctp_association *asoc,
				    __be16 hmac_id)
{
	struct sctp_hmac_algo_param *hmacs;
	__u16 n_elt;

	if (!asoc)
		return 0;

	hmacs = (struct sctp_hmac_algo_param *)asoc->c.auth_hmacs;
	n_elt = (ntohs(hmacs->param_hdr.length) - sizeof(sctp_paramhdr_t)) >> 1;

	return __sctp_auth_find_hmacid(hmacs->hmac_ids, n_elt, hmac_id);
}