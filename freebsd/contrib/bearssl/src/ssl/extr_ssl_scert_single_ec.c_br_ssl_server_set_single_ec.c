#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  br_x509_certificate ;
struct TYPE_7__ {size_t chain_len; unsigned int allowed_usages; unsigned int cert_issuer_key_type; int /*<<< orphan*/ * vtable; int /*<<< orphan*/  iecdsa; int /*<<< orphan*/  const* iec; int /*<<< orphan*/ * mhash; int /*<<< orphan*/  const* sk; int /*<<< orphan*/  const* chain; } ;
struct TYPE_8__ {TYPE_2__ single_ec; } ;
struct TYPE_6__ {int /*<<< orphan*/  mhash; } ;
struct TYPE_9__ {TYPE_3__ chain_handler; int /*<<< orphan*/ ** policy_vtable; TYPE_1__ eng; } ;
typedef  TYPE_4__ br_ssl_server_context ;
typedef  int /*<<< orphan*/  br_ecdsa_sign ;
typedef  int /*<<< orphan*/  br_ec_private_key ;
typedef  int /*<<< orphan*/  br_ec_impl ;

/* Variables and functions */
 int /*<<< orphan*/  se_policy_vtable ; 

void
br_ssl_server_set_single_ec(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk, unsigned allowed_usages,
	unsigned cert_issuer_key_type,
	const br_ec_impl *iec, br_ecdsa_sign iecdsa)
{
	cc->chain_handler.single_ec.vtable = &se_policy_vtable;
	cc->chain_handler.single_ec.chain = chain;
	cc->chain_handler.single_ec.chain_len = chain_len;
	cc->chain_handler.single_ec.sk = sk;
	cc->chain_handler.single_ec.allowed_usages = allowed_usages;
	cc->chain_handler.single_ec.cert_issuer_key_type = cert_issuer_key_type;
	cc->chain_handler.single_ec.mhash = &cc->eng.mhash;
	cc->chain_handler.single_ec.iec = iec;
	cc->chain_handler.single_ec.iecdsa = iecdsa;
	cc->policy_vtable = &cc->chain_handler.single_ec.vtable;
}