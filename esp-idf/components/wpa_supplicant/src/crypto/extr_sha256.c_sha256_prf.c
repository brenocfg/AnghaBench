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
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  length_le ;

/* Variables and functions */
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t os_strlen (char const*) ; 

void 
sha256_prf(const u8 *key, size_t key_len, const char *label,
		const u8 *data, size_t data_len, u8 *buf, size_t buf_len)
{
	u16 counter = 1;
	size_t pos, plen;
	u8 hash[SHA256_MAC_LEN];
	const u8 *addr[4];
	size_t len[4];
	u8 counter_le[2], length_le[2];

	addr[0] = counter_le;
	len[0] = 2;
	addr[1] = (u8 *) label;
	len[1] = os_strlen(label);
	addr[2] = data;
	len[2] = data_len;
	addr[3] = length_le;
	len[3] = sizeof(length_le);

	WPA_PUT_LE16(length_le, buf_len * 8);
	pos = 0;
	while (pos < buf_len) {
		plen = buf_len - pos;
		WPA_PUT_LE16(counter_le, counter);
		if (plen >= SHA256_MAC_LEN) {
			hmac_sha256_vector(key, key_len, 4, addr, len,
					   &buf[pos]);
			pos += SHA256_MAC_LEN;
		} else {
			hmac_sha256_vector(key, key_len, 4, addr, len, hash);
			os_memcpy(&buf[pos], hash, plen);
			break;
		}
		counter++;
	}
}