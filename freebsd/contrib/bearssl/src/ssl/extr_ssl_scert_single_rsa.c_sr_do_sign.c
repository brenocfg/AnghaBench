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
struct TYPE_3__ {TYPE_2__* sk; scalar_t__ (* irsasign ) (unsigned char const*,unsigned char*,size_t,TYPE_2__*,unsigned char*) ;} ;
typedef  TYPE_1__ br_ssl_server_policy_rsa_context ;
typedef  int /*<<< orphan*/  br_ssl_server_policy_class ;
struct TYPE_4__ {int n_bitlen; } ;

/* Variables and functions */
 unsigned char** HASH_OID ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 scalar_t__ stub1 (unsigned char const*,unsigned char*,size_t,TYPE_2__*,unsigned char*) ; 

__attribute__((used)) static size_t
sr_do_sign(const br_ssl_server_policy_class **pctx,
	unsigned algo_id, unsigned char *data, size_t hv_len, size_t len)
{
	br_ssl_server_policy_rsa_context *pc;
	unsigned char hv[64];
	size_t sig_len;
	const unsigned char *hash_oid;

	pc = (br_ssl_server_policy_rsa_context *)pctx;
	memcpy(hv, data, hv_len);
	algo_id &= 0xFF;
	if (algo_id == 0) {
		hash_oid = NULL;
	} else if (algo_id >= 2 && algo_id <= 6) {
		hash_oid = HASH_OID[algo_id - 2];
	} else {
		return 0;
	}
	sig_len = (pc->sk->n_bitlen + 7) >> 3;
	if (len < sig_len) {
		return 0;
	}
	return pc->irsasign(hash_oid, hv, hv_len, pc->sk, data) ? sig_len : 0;
}