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
typedef  unsigned char HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  A1 ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HMAC_CTX_cleanup (unsigned char*) ; 
 int /*<<< orphan*/  HMAC_CTX_free (unsigned char*) ; 
 unsigned char* HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (unsigned char*,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (unsigned char*,unsigned char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  Zero (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

void Enc_tls1_P_hash(const EVP_MD *md, const unsigned char *sec, int sec_len,
				 const unsigned char *seed, int seed_len, unsigned char *out, int olen)
{
	int chunk,n;
	unsigned int j;
	HMAC_CTX *ctx;
	HMAC_CTX *ctx_tmp;
	unsigned char A1[EVP_MAX_MD_SIZE];
	unsigned int A1_len;

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	ctx = HMAC_CTX_new();
	ctx_tmp = HMAC_CTX_new();
#else
	HMAC_CTX ctx_;
	HMAC_CTX ctx_tmp_;
	ctx = &ctx_;
	ctx_tmp = &ctx_tmp_;
	Zero(ctx, sizeof(HMAC_CTX));
	Zero(ctx_tmp, sizeof(HMAC_CTX));
#endif
	chunk=EVP_MD_size(md);

	HMAC_Init_ex(ctx,sec,sec_len,md, NULL);
	HMAC_Init_ex(ctx_tmp,sec,sec_len,md, NULL);
	HMAC_Update(ctx,seed,seed_len);
	HMAC_Final(ctx,A1,&A1_len);

	n=0;
	for (;;)
	{
		HMAC_Init_ex(ctx,NULL,0,NULL,NULL); /* re-init */
		HMAC_Init_ex(ctx_tmp,NULL,0,NULL,NULL); /* re-init */
		HMAC_Update(ctx,A1,A1_len);
		HMAC_Update(ctx_tmp,A1,A1_len);
		HMAC_Update(ctx,seed,seed_len);

		if (olen > chunk)
		{
			HMAC_Final(ctx,out,&j);
			out+=j;
			olen-=j;
			HMAC_Final(ctx_tmp,A1,&A1_len); /* calc the next A1 value */
		}
		else	/* last one */
		{
			HMAC_Final(ctx,A1,&A1_len);
			memcpy(out,A1,olen);
			break;
		}
	}
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	HMAC_CTX_free(ctx);
	HMAC_CTX_free(ctx_tmp);
#else
	HMAC_CTX_cleanup(ctx);
	HMAC_CTX_cleanup(ctx_tmp);
#endif
	Zero (A1, sizeof(A1));
}