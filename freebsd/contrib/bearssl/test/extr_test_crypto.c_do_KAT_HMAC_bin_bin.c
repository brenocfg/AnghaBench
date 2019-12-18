#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  br_hmac_key_context ;
typedef  int /*<<< orphan*/  br_hmac_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  br_hmac_out (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  br_hmac_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 size_t hextobin (unsigned char*,char const*) ; 

__attribute__((used)) static void
do_KAT_HMAC_bin_bin(const br_hash_class *digest_class,
	const void *key, size_t key_len,
	const void *data, size_t data_len, const char *href)
{
	br_hmac_key_context kc;
	br_hmac_context ctx;
	unsigned char tmp[64], ref[64];
	size_t u, len;

	len = hextobin(ref, href);
	br_hmac_key_init(&kc, digest_class, key, key_len);
	br_hmac_init(&ctx, &kc, 0);
	br_hmac_update(&ctx, data, data_len);
	br_hmac_out(&ctx, tmp);
	check_equals("KAT HMAC 1", tmp, ref, len);

	br_hmac_init(&ctx, &kc, 0);
	for (u = 0; u < data_len; u ++) {
		br_hmac_update(&ctx, (const unsigned char *)data + u, 1);
	}
	br_hmac_out(&ctx, tmp);
	check_equals("KAT HMAC 2", tmp, ref, len);

	for (u = 0; u < data_len; u ++) {
		br_hmac_init(&ctx, &kc, 0);
		br_hmac_update(&ctx, data, u);
		br_hmac_out(&ctx, tmp);
		br_hmac_update(&ctx,
			(const unsigned char *)data + u, data_len - u);
		br_hmac_out(&ctx, tmp);
		check_equals("KAT HMAC 3", tmp, ref, len);
	}
}