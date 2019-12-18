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
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 size_t AAD_LEN ; 
 int CMAC_TLEN ; 
 int /*<<< orphan*/  aes_128_cmac_vector (struct crypto_cipher*,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ieee80211_aes_cmac(struct crypto_cipher *tfm, const u8 *aad,
			const u8 *data, size_t data_len, u8 *mic)
{
	const u8 *addr[3];
	size_t len[3];
	u8 zero[CMAC_TLEN];

	memset(zero, 0, CMAC_TLEN);
	addr[0] = aad;
	len[0] = AAD_LEN;
	addr[1] = data;
	len[1] = data_len - CMAC_TLEN;
	addr[2] = zero;
	len[2] = CMAC_TLEN;

	aes_128_cmac_vector(tfm, 3, addr, len, mic);
}