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
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  SHA1_Final (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__,int) ; 

void
sec_hash_48(uint8 * out, uint8 * in, uint8 * salt1, uint8 * salt2, uint8 salt)
{
	uint8 shasig[20];
	uint8 pad[4];
	SHA_CTX sha;
	MD5_CTX md5;
	int i;

	for (i = 0; i < 3; i++)
	{
		memset(pad, salt + i, i + 1);

		SHA1_Init(&sha);
		SHA1_Update(&sha, pad, i + 1);
		SHA1_Update(&sha, in, 48);
		SHA1_Update(&sha, salt1, 32);
		SHA1_Update(&sha, salt2, 32);
		SHA1_Final(shasig, &sha);

		MD5_Init(&md5);
		MD5_Update(&md5, in, 48);
		MD5_Update(&md5, shasig, 20);
		MD5_Final(&out[i * 16], &md5);
	}
}