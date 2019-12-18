#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  br_ssl_client_context ;
struct TYPE_5__ {int /*<<< orphan*/  chain_len; int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ br_ssl_client_certificate_rsa_context ;
typedef  int /*<<< orphan*/  br_ssl_client_certificate_class ;
struct TYPE_6__ {int hash_id; int /*<<< orphan*/  chain_len; int /*<<< orphan*/  chain; int /*<<< orphan*/  auth_type; } ;
typedef  TYPE_2__ br_ssl_client_certificate ;

/* Variables and functions */
 int /*<<< orphan*/  BR_AUTH_RSA ; 
 int br_ssl_choose_hash (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cc_choose(const br_ssl_client_certificate_class **pctx,
	const br_ssl_client_context *cc, uint32_t auth_types,
	br_ssl_client_certificate *choices)
{
	br_ssl_client_certificate_rsa_context *zc;
	int x;

	(void)cc;
	zc = (br_ssl_client_certificate_rsa_context *)pctx;
	x = br_ssl_choose_hash((unsigned)auth_types);
	if (x == 0 && (auth_types & 1) == 0) {
		memset(choices, 0, sizeof *choices);
	}
	choices->auth_type = BR_AUTH_RSA;
	choices->hash_id = x;
	choices->chain = zc->chain;
	choices->chain_len = zc->chain_len;
}