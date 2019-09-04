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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int mptcp_key_t ;
typedef  int /*<<< orphan*/  key_opad ;
typedef  int /*<<< orphan*/  key_ipad ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int SHA1_RESULTLEN ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

void
mptcp_hmac_sha1(mptcp_key_t key1, mptcp_key_t key2,
	u_int32_t rand1, u_int32_t rand2, u_char *digest)
{
	SHA1_CTX  sha1ctxt;
	mptcp_key_t key_ipad[8] = {0}; /* key XOR'd with inner pad */
	mptcp_key_t key_opad[8] = {0}; /* key XOR'd with outer pad */
	u_int32_t data[2];
	int i;

	bzero(digest, SHA1_RESULTLEN);

	/* Set up the Key for HMAC */
	key_ipad[0] = key1;
	key_ipad[1] = key2;

	key_opad[0] = key1;
	key_opad[1] = key2;

	/* Set up the message for HMAC */
	data[0] = rand1;
	data[1] = rand2;

	/* Key is 512 block length, so no need to compute hash */

	/* Compute SHA1(Key XOR opad, SHA1(Key XOR ipad, data)) */

	for (i = 0; i < 8; i++) {
		key_ipad[i] ^= 0x3636363636363636;
		key_opad[i] ^= 0x5c5c5c5c5c5c5c5c;
	}

	/* Perform inner SHA1 */
	SHA1Init(&sha1ctxt);
	SHA1Update(&sha1ctxt, (unsigned char *)key_ipad, sizeof (key_ipad));
	SHA1Update(&sha1ctxt, (unsigned char *)data, sizeof (data));
	SHA1Final(digest, &sha1ctxt);

	/* Perform outer SHA1 */
	SHA1Init(&sha1ctxt);
	SHA1Update(&sha1ctxt, (unsigned char *)key_opad, sizeof (key_opad));
	SHA1Update(&sha1ctxt, (unsigned char *)digest, SHA1_RESULTLEN);
	SHA1Final(digest, &sha1ctxt);
}