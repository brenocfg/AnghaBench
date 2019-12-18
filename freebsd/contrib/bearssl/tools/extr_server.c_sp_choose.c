#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ verbose; int /*<<< orphan*/  chain_len; int /*<<< orphan*/  chain; int /*<<< orphan*/  cert_signer_algo; TYPE_1__* sk; int /*<<< orphan*/  cbhash; } ;
typedef  TYPE_2__ policy_context ;
typedef  void** br_suite_translated ;
typedef  int /*<<< orphan*/  br_ssl_server_policy_class ;
struct TYPE_11__ {int client_max_version; int /*<<< orphan*/  eng; } ;
typedef  TYPE_3__ br_ssl_server_context ;
struct TYPE_12__ {void* cipher_suite; int algo_id; int /*<<< orphan*/  chain_len; int /*<<< orphan*/  chain; } ;
typedef  TYPE_4__ br_ssl_server_choices ;
struct TYPE_9__ {int /*<<< orphan*/  key_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_KEYTYPE_EC ; 
 int /*<<< orphan*/  BR_KEYTYPE_RSA ; 
#define  BR_SSL30 136 
#define  BR_SSLKEYX_ECDHE_ECDSA 135 
#define  BR_SSLKEYX_ECDHE_RSA 134 
#define  BR_SSLKEYX_ECDH_ECDSA 133 
#define  BR_SSLKEYX_ECDH_RSA 132 
#define  BR_SSLKEYX_RSA 131 
#define  BR_TLS10 130 
#define  BR_TLS11 129 
#define  BR_TLS12 128 
 int /*<<< orphan*/  br_sha1_ID ; 
 int const br_ssl_engine_get_version (int /*<<< orphan*/ *) ; 
 unsigned int br_ssl_server_get_client_hashes (TYPE_3__ const*) ; 
 void*** br_ssl_server_get_client_suites (TYPE_3__ const*,size_t*) ; 
 unsigned int choose_hash (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_suite_name_ext (void*,char*,int) ; 
 int /*<<< orphan*/  print_hashes (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
sp_choose(const br_ssl_server_policy_class **pctx,
	const br_ssl_server_context *cc,
	br_ssl_server_choices *choices)
{
	policy_context *pc;
	const br_suite_translated *st;
	size_t u, st_num;
	unsigned chashes;

	pc = (policy_context *)pctx;
	st = br_ssl_server_get_client_suites(cc, &st_num);
	chashes = br_ssl_server_get_client_hashes(cc);
	if (pc->verbose) {
		fprintf(stderr, "Client parameters:\n");
		fprintf(stderr, "   Maximum version:      ");
		switch (cc->client_max_version) {
		case BR_SSL30:
			fprintf(stderr, "SSL 3.0");
			break;
		case BR_TLS10:
			fprintf(stderr, "TLS 1.0");
			break;
		case BR_TLS11:
			fprintf(stderr, "TLS 1.1");
			break;
		case BR_TLS12:
			fprintf(stderr, "TLS 1.2");
			break;
		default:
			fprintf(stderr, "unknown (0x%04X)",
				(unsigned)cc->client_max_version);
			break;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "   Compatible cipher suites:\n");
		for (u = 0; u < st_num; u ++) {
			char csn[80];

			get_suite_name_ext(st[u][0], csn, sizeof csn);
			fprintf(stderr, "      %s\n", csn);
		}
		fprintf(stderr, "   Common sign+hash functions:\n");
		if ((chashes & 0xFF) != 0) {
			fprintf(stderr, "      with RSA:");
			print_hashes(chashes);
			fprintf(stderr, "\n");
		}
		if ((chashes >> 8) != 0) {
			fprintf(stderr, "      with ECDSA:");
			print_hashes(chashes >> 8);
			fprintf(stderr, "\n");
		}
	}
	for (u = 0; u < st_num; u ++) {
		unsigned tt;

		tt = st[u][1];
		switch (tt >> 12) {
		case BR_SSLKEYX_RSA:
			if (pc->sk->key_type == BR_KEYTYPE_RSA) {
				choices->cipher_suite = st[u][0];
				goto choose_ok;
			}
			break;
		case BR_SSLKEYX_ECDHE_RSA:
			if (pc->sk->key_type == BR_KEYTYPE_RSA) {
				choices->cipher_suite = st[u][0];
				if (br_ssl_engine_get_version(&cc->eng)
					< BR_TLS12)
				{
					if (pc->cbhash) {
						choices->algo_id = 0x0001;
					} else {
						choices->algo_id = 0xFF00;
					}
				} else {
					unsigned id;

					id = choose_hash(chashes);
					if (pc->cbhash) {
						choices->algo_id =
							(id << 8) + 0x01;
					} else {
						choices->algo_id = 0xFF00 + id;
					}
				}
				goto choose_ok;
			}
			break;
		case BR_SSLKEYX_ECDHE_ECDSA:
			if (pc->sk->key_type == BR_KEYTYPE_EC) {
				choices->cipher_suite = st[u][0];
				if (br_ssl_engine_get_version(&cc->eng)
					< BR_TLS12)
				{
					if (pc->cbhash) {
						choices->algo_id = 0x0203;
					} else {
						choices->algo_id =
							0xFF00 + br_sha1_ID;
					}
				} else {
					unsigned id;

					id = choose_hash(chashes >> 8);
					if (pc->cbhash) {
						choices->algo_id =
							(id << 8) + 0x03;
					} else {
						choices->algo_id =
							0xFF00 + id;
					}
				}
				goto choose_ok;
			}
			break;
		case BR_SSLKEYX_ECDH_RSA:
			if (pc->sk->key_type == BR_KEYTYPE_EC
				&& pc->cert_signer_algo == BR_KEYTYPE_RSA)
			{
				choices->cipher_suite = st[u][0];
				goto choose_ok;
			}
			break;
		case BR_SSLKEYX_ECDH_ECDSA:
			if (pc->sk->key_type == BR_KEYTYPE_EC
				&& pc->cert_signer_algo == BR_KEYTYPE_EC)
			{
				choices->cipher_suite = st[u][0];
				goto choose_ok;
			}
			break;
		}
	}
	return 0;

choose_ok:
	choices->chain = pc->chain;
	choices->chain_len = pc->chain_len;
	if (pc->verbose) {
		char csn[80];

		get_suite_name_ext(choices->cipher_suite, csn, sizeof csn);
		fprintf(stderr, "Using: %s\n", csn);
	}
	return 1;
}