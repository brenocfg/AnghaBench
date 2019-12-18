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
typedef  int /*<<< orphan*/  br_x509_certificate ;
struct TYPE_5__ {size_t chain_len; int /*<<< orphan*/ * vtable; int /*<<< orphan*/  irsasign; int /*<<< orphan*/  const* sk; int /*<<< orphan*/  const* chain; } ;
struct TYPE_6__ {TYPE_1__ single_rsa; } ;
struct TYPE_7__ {TYPE_2__ client_auth; int /*<<< orphan*/ ** client_auth_vtable; } ;
typedef  TYPE_3__ br_ssl_client_context ;
typedef  int /*<<< orphan*/  br_rsa_private_key ;
typedef  int /*<<< orphan*/  br_rsa_pkcs1_sign ;

/* Variables and functions */
 int /*<<< orphan*/  ccert_vtable ; 

void
br_ssl_client_set_single_rsa(br_ssl_client_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk, br_rsa_pkcs1_sign irsasign)
{
	cc->client_auth.single_rsa.vtable = &ccert_vtable;
	cc->client_auth.single_rsa.chain = chain;
	cc->client_auth.single_rsa.chain_len = chain_len;
	cc->client_auth.single_rsa.sk = sk;
	cc->client_auth.single_rsa.irsasign = irsasign;
	cc->client_auth_vtable = &cc->client_auth.single_rsa.vtable;
}