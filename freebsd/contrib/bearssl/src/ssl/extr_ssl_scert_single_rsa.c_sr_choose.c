#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void** br_suite_translated ;
struct TYPE_12__ {int allowed_usages; int /*<<< orphan*/  chain_len; int /*<<< orphan*/  chain; } ;
typedef  TYPE_3__ br_ssl_server_policy_rsa_context ;
typedef  int /*<<< orphan*/  br_ssl_server_policy_class ;
struct TYPE_10__ {scalar_t__ version; } ;
struct TYPE_11__ {TYPE_1__ session; } ;
struct TYPE_13__ {TYPE_2__ eng; } ;
typedef  TYPE_4__ br_ssl_server_context ;
struct TYPE_14__ {unsigned int algo_id; void* cipher_suite; int /*<<< orphan*/  chain_len; int /*<<< orphan*/  chain; } ;
typedef  TYPE_5__ br_ssl_server_choices ;

/* Variables and functions */
 int BR_KEYTYPE_KEYX ; 
 int BR_KEYTYPE_SIGN ; 
#define  BR_SSLKEYX_ECDHE_RSA 129 
#define  BR_SSLKEYX_RSA 128 
 scalar_t__ BR_TLS12 ; 
 unsigned int br_ssl_choose_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_server_get_client_hashes (TYPE_4__ const*) ; 
 void*** br_ssl_server_get_client_suites (TYPE_4__ const*,size_t*) ; 

__attribute__((used)) static int
sr_choose(const br_ssl_server_policy_class **pctx,
	const br_ssl_server_context *cc,
	br_ssl_server_choices *choices)
{
	br_ssl_server_policy_rsa_context *pc;
	const br_suite_translated *st;
	size_t u, st_num;
	unsigned hash_id;
	int fh;

	pc = (br_ssl_server_policy_rsa_context *)pctx;
	st = br_ssl_server_get_client_suites(cc, &st_num);
	if (cc->eng.session.version < BR_TLS12) {
		hash_id = 0;
		fh = 1;
	} else {
		hash_id = br_ssl_choose_hash(
			br_ssl_server_get_client_hashes(cc));
		fh = (hash_id != 0);
	}
	choices->chain = pc->chain;
	choices->chain_len = pc->chain_len;
	for (u = 0; u < st_num; u ++) {
		unsigned tt;

		tt = st[u][1];
		switch (tt >> 12) {
		case BR_SSLKEYX_RSA:
			if ((pc->allowed_usages & BR_KEYTYPE_KEYX) != 0) {
				choices->cipher_suite = st[u][0];
				return 1;
			}
			break;
		case BR_SSLKEYX_ECDHE_RSA:
			if ((pc->allowed_usages & BR_KEYTYPE_SIGN) != 0 && fh) {
				choices->cipher_suite = st[u][0];
				choices->algo_id = hash_id + 0xFF00;
				return 1;
			}
			break;
		}
	}
	return 0;
}