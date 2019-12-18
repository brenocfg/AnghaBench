#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* data; size_t len; } ;
typedef  TYPE_1__ br_tls_prf_seed_chunk ;
typedef  int /*<<< orphan*/  br_hmac_key_context ;
typedef  int /*<<< orphan*/  br_hmac_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 size_t br_digest_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  br_hmac_out (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  br_hmac_update (int /*<<< orphan*/ *,...) ; 

void
br_tls_phash(void *dst, size_t len,
	const br_hash_class *dig,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed)
{
	unsigned char *buf;
	unsigned char tmp[64], a[64];
	br_hmac_key_context kc;
	br_hmac_context hc;
	size_t label_len, hlen, u;

	if (len == 0) {
		return;
	}
	buf = dst;
	for (label_len = 0; label[label_len]; label_len ++);
	hlen = br_digest_size(dig);
	br_hmac_key_init(&kc, dig, secret, secret_len);
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, label, label_len);
	for (u = 0; u < seed_num; u ++) {
		br_hmac_update(&hc, seed[u].data, seed[u].len);
	}
	br_hmac_out(&hc, a);
	for (;;) {
		br_hmac_init(&hc, &kc, 0);
		br_hmac_update(&hc, a, hlen);
		br_hmac_update(&hc, label, label_len);
		for (u = 0; u < seed_num; u ++) {
			br_hmac_update(&hc, seed[u].data, seed[u].len);
		}
		br_hmac_out(&hc, tmp);
		for (u = 0; u < hlen && u < len; u ++) {
			buf[u] ^= tmp[u];
		}
		buf += u;
		len -= u;
		if (len == 0) {
			return;
		}
		br_hmac_init(&hc, &kc, 0);
		br_hmac_update(&hc, a, hlen);
		br_hmac_out(&hc, a);
	}
}