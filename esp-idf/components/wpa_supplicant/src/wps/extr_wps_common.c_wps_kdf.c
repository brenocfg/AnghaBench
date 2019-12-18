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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  key_bits ;
typedef  int /*<<< orphan*/  i_buf ;

/* Variables and functions */
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t os_strlen (char const*) ; 

void wps_kdf(const u8 *key, const u8 *label_prefix, size_t label_prefix_len,
	     const char *label, u8 *res, size_t res_len)
{
	u8 i_buf[4], key_bits[4];
	const u8 *addr[4];
	size_t len[4];
	int i, iter;
	u8 hash[SHA256_MAC_LEN], *opos;
	size_t left;

	WPA_PUT_BE32(key_bits, res_len * 8);

	addr[0] = i_buf;
	len[0] = sizeof(i_buf);
	addr[1] = label_prefix;
	len[1] = label_prefix_len;
	addr[2] = (const u8 *) label;
	len[2] = os_strlen(label);
	addr[3] = key_bits;
	len[3] = sizeof(key_bits);

	iter = (res_len + SHA256_MAC_LEN - 1) / SHA256_MAC_LEN;
	opos = res;
	left = res_len;

	for (i = 1; i <= iter; i++) {
		WPA_PUT_BE32(i_buf, i);
		hmac_sha256_vector(key, SHA256_MAC_LEN, 4, addr, len, hash);
		if (i < iter) {
			os_memcpy(opos, hash, SHA256_MAC_LEN);
			opos += SHA256_MAC_LEN;
			left -= SHA256_MAC_LEN;
		} else
			os_memcpy(opos, hash, left);
	}
}