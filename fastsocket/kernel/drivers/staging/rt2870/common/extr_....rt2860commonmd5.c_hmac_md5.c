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
typedef  int u8 ;
typedef  int /*<<< orphan*/  k_opad ;
typedef  int /*<<< orphan*/  k_ipad ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  NdisMoveMemory (int*,int*,size_t) ; 
 int /*<<< orphan*/  NdisZeroMemory (int*,int) ; 

void hmac_md5(u8 *key, size_t key_len, u8 *data, size_t data_len, u8 *mac)
{
	MD5_CTX	context;
    u8 k_ipad[65]; /* inner padding - key XORd with ipad */
    u8 k_opad[65]; /* outer padding - key XORd with opad */
    u8 tk[16];
	int	i;

	//assert(key != NULL && data != NULL && mac != NULL);

	/* if key is longer	than 64	bytes reset	it to key =	MD5(key) */
	if (key_len	> 64) {
		MD5_CTX	ttcontext;

		MD5Init(&ttcontext);
		MD5Update(&ttcontext, key, key_len);
		MD5Final(tk, &ttcontext);
		//key=(PUCHAR)ttcontext.buf;
		key	= tk;
		key_len	= 16;
	}

	/* the HMAC_MD5	transform looks	like:
	 *
	 * MD5(K XOR opad, MD5(K XOR ipad, text))
	 *
	 * where K is an n byte	key
	 * ipad	is the byte	0x36 repeated 64 times
	 * opad	is the byte	0x5c repeated 64 times
	 * and text	is the data	being protected	*/

	/* start out by	storing	key	in pads	*/
	NdisZeroMemory(k_ipad, sizeof(k_ipad));
	NdisZeroMemory(k_opad,	sizeof(k_opad));
	//assert(key_len < sizeof(k_ipad));
	NdisMoveMemory(k_ipad, key,	key_len);
	NdisMoveMemory(k_opad, key,	key_len);

	/* XOR key with	ipad and opad values */
	for	(i = 0;	i <	64;	i++) {
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}

	/* perform inner MD5 */
	MD5Init(&context);					 /*	init context for 1st pass */
	MD5Update(&context,	k_ipad,	64);	 /*	start with inner pad */
	MD5Update(&context,	data, data_len); /*	then text of datagram */
	MD5Final(mac, &context);			 /*	finish up 1st pass */

	/* perform outer MD5 */
	MD5Init(&context);					 /*	init context for 2nd pass */
	MD5Update(&context,	k_opad,	64);	 /*	start with outer pad */
	MD5Update(&context,	mac, 16);		 /*	then results of	1st	hash */
	MD5Final(mac, &context);			 /*	finish up 2nd pass */
}