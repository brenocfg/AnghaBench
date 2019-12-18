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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_md5 () ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/  Enc_tls1_P_hash (int /*<<< orphan*/  const*,unsigned char const*,int,unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  Free (unsigned char*) ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void Enc_tls1_PRF(unsigned char *label, int label_len, const unsigned char *sec,
				  int slen, unsigned char *out1, int olen)
{
	const EVP_MD *md5 = EVP_md5();
	const EVP_MD *sha1 = EVP_sha1();
	int len,i;
	const unsigned char *S1,*S2;
	unsigned char *out2;

	out2 = (unsigned char *) Malloc (olen);

	len=slen/2;
	S1=sec;
	S2= &(sec[len]);
	len+=(slen&1); /* add for odd, make longer */


	Enc_tls1_P_hash(md5 ,S1,len,label,label_len,out1,olen);
	Enc_tls1_P_hash(sha1,S2,len,label,label_len,out2,olen);

	for (i=0; i<olen; i++)
		out1[i]^=out2[i];

	memset (out2, 0, olen);
	Free(out2);
}