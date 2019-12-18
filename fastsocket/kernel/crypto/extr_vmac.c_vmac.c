#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__* cached_aes; scalar_t__* cached_nonce; } ;
struct vmac_ctx_t {TYPE_1__ __vmac_ctx; int /*<<< orphan*/  child; } ;

/* Variables and functions */
 scalar_t__ be64_to_cpup (scalar_t__*) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 
 scalar_t__ vhash (unsigned char*,unsigned int,scalar_t__*,TYPE_1__*) ; 

__attribute__((used)) static u64 vmac(unsigned char m[], unsigned int mbytes,
			unsigned char n[16], u64 *tagl,
			struct vmac_ctx_t *ctx)
{
	u64 *in_n, *out_p;
	u64 p, h;
	int i;

	in_n = ctx->__vmac_ctx.cached_nonce;
	out_p = ctx->__vmac_ctx.cached_aes;

	i = n[15] & 1;
	if ((*(u64 *)(n+8) != in_n[1]) || (*(u64 *)(n) != in_n[0])) {
		in_n[0] = *(u64 *)(n);
		in_n[1] = *(u64 *)(n+8);
		((unsigned char *)in_n)[15] &= 0xFE;
		crypto_cipher_encrypt_one(ctx->child,
			(unsigned char *)out_p, (unsigned char *)in_n);

		((unsigned char *)in_n)[15] |= (unsigned char)(1-i);
	}
	p = be64_to_cpup(out_p + i);
	h = vhash(m, mbytes, (u64 *)0, &ctx->__vmac_ctx);
	return le64_to_cpu(p + h);
}