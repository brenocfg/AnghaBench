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
typedef  int u32 ;
struct blkcipher_alg {scalar_t__ ivsize; } ;
struct crypto_alg {unsigned int cra_ctxsize; scalar_t__ cra_alignmask; struct blkcipher_alg cra_blkcipher; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,unsigned long) ; 
 int CRYPTO_ALG_TYPE_MASK ; 

__attribute__((used)) static unsigned int crypto_blkcipher_ctxsize(struct crypto_alg *alg, u32 type,
					     u32 mask)
{
	struct blkcipher_alg *cipher = &alg->cra_blkcipher;
	unsigned int len = alg->cra_ctxsize;

	if ((mask & CRYPTO_ALG_TYPE_MASK) == CRYPTO_ALG_TYPE_MASK &&
	    cipher->ivsize) {
		len = ALIGN(len, (unsigned long)alg->cra_alignmask + 1);
		len += cipher->ivsize;
	}

	return len;
}