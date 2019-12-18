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
struct TYPE_2__ {size_t (* iecdsa ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ;int /*<<< orphan*/  sk; int /*<<< orphan*/  iec; int /*<<< orphan*/  mhash; } ;
typedef  TYPE_1__ br_ssl_server_policy_ec_context ;
typedef  int /*<<< orphan*/  br_ssl_server_policy_class ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/ * br_multihash_getimpl (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static size_t
se_do_sign(const br_ssl_server_policy_class **pctx,
	unsigned algo_id, unsigned char *data, size_t hv_len, size_t len)
{
	br_ssl_server_policy_ec_context *pc;
	unsigned char hv[64];
	const br_hash_class *hc;

	algo_id &= 0xFF;
	pc = (br_ssl_server_policy_ec_context *)pctx;
	hc = br_multihash_getimpl(pc->mhash, algo_id);
	if (hc == NULL) {
		return 0;
	}
	memcpy(hv, data, hv_len);
	if (len < 139) {
		return 0;
	}
	return pc->iecdsa(pc->iec, hc, hv, pc->sk, data);
}