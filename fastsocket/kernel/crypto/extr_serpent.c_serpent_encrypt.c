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
typedef  int /*<<< orphan*/  u32 ;
struct serpent_ctx {int /*<<< orphan*/ * expkey; } ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  K (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct serpent_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void serpent_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct serpent_ctx *ctx = crypto_tfm_ctx(tfm);
	const u32
		*k = ctx->expkey;
	const __le32 *s = (const __le32 *)src;
	__le32	*d = (__le32 *)dst;
	u32	r0, r1, r2, r3, r4;

/*
 * Note: The conversions between u8* and u32* might cause trouble
 * on architectures with stricter alignment rules than x86
 */

	r0 = le32_to_cpu(s[0]);
	r1 = le32_to_cpu(s[1]);
	r2 = le32_to_cpu(s[2]);
	r3 = le32_to_cpu(s[3]);

				 K(r0,r1,r2,r3,0);
	S0(r0,r1,r2,r3,r4);	LK(r2,r1,r3,r0,r4,1);
	S1(r2,r1,r3,r0,r4);	LK(r4,r3,r0,r2,r1,2);
	S2(r4,r3,r0,r2,r1);	LK(r1,r3,r4,r2,r0,3);
	S3(r1,r3,r4,r2,r0);	LK(r2,r0,r3,r1,r4,4);
	S4(r2,r0,r3,r1,r4);	LK(r0,r3,r1,r4,r2,5);
	S5(r0,r3,r1,r4,r2);	LK(r2,r0,r3,r4,r1,6);
	S6(r2,r0,r3,r4,r1);	LK(r3,r1,r0,r4,r2,7);
	S7(r3,r1,r0,r4,r2);	LK(r2,r0,r4,r3,r1,8);
	S0(r2,r0,r4,r3,r1);	LK(r4,r0,r3,r2,r1,9);
	S1(r4,r0,r3,r2,r1);	LK(r1,r3,r2,r4,r0,10);
	S2(r1,r3,r2,r4,r0);	LK(r0,r3,r1,r4,r2,11);
	S3(r0,r3,r1,r4,r2);	LK(r4,r2,r3,r0,r1,12);
	S4(r4,r2,r3,r0,r1);	LK(r2,r3,r0,r1,r4,13);
	S5(r2,r3,r0,r1,r4);	LK(r4,r2,r3,r1,r0,14);
	S6(r4,r2,r3,r1,r0);	LK(r3,r0,r2,r1,r4,15);
	S7(r3,r0,r2,r1,r4);	LK(r4,r2,r1,r3,r0,16);
	S0(r4,r2,r1,r3,r0);	LK(r1,r2,r3,r4,r0,17);
	S1(r1,r2,r3,r4,r0);	LK(r0,r3,r4,r1,r2,18);
	S2(r0,r3,r4,r1,r2);	LK(r2,r3,r0,r1,r4,19);
	S3(r2,r3,r0,r1,r4);	LK(r1,r4,r3,r2,r0,20);
	S4(r1,r4,r3,r2,r0);	LK(r4,r3,r2,r0,r1,21);
	S5(r4,r3,r2,r0,r1);	LK(r1,r4,r3,r0,r2,22);
	S6(r1,r4,r3,r0,r2);	LK(r3,r2,r4,r0,r1,23);
	S7(r3,r2,r4,r0,r1);	LK(r1,r4,r0,r3,r2,24);
	S0(r1,r4,r0,r3,r2);	LK(r0,r4,r3,r1,r2,25);
	S1(r0,r4,r3,r1,r2);	LK(r2,r3,r1,r0,r4,26);
	S2(r2,r3,r1,r0,r4);	LK(r4,r3,r2,r0,r1,27);
	S3(r4,r3,r2,r0,r1);	LK(r0,r1,r3,r4,r2,28);
	S4(r0,r1,r3,r4,r2);	LK(r1,r3,r4,r2,r0,29);
	S5(r1,r3,r4,r2,r0);	LK(r0,r1,r3,r2,r4,30);
	S6(r0,r1,r3,r2,r4);	LK(r3,r4,r1,r2,r0,31);
	S7(r3,r4,r1,r2,r0);	 K(r0,r1,r2,r3,32);

	d[0] = cpu_to_le32(r0);
	d[1] = cpu_to_le32(r1);
	d[2] = cpu_to_le32(r2);
	d[3] = cpu_to_le32(r3);
}