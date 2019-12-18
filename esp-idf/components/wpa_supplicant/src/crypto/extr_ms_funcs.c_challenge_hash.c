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
typedef  unsigned char u8 ;

/* Variables and functions */
 int SHA1_MAC_LEN ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,unsigned char*,int) ; 
 scalar_t__ sha1_vector (int,unsigned char const**,size_t*,unsigned char*) ; 

__attribute__((used)) static int challenge_hash(const u8 *peer_challenge, const u8 *auth_challenge,
	       const u8 *username, size_t username_len,
	       u8 *challenge)
{
	u8 hash[SHA1_MAC_LEN];
	const unsigned char *addr[3];
	size_t len[3];

	addr[0] = peer_challenge;
	len[0] = 16;
	addr[1] = auth_challenge;
	len[1] = 16;
	addr[2] = username;
	len[2] = username_len;

	if (sha1_vector(3, addr, len, hash))
		return -1;
	os_memcpy(challenge, hash, 8);
	return 0;
}