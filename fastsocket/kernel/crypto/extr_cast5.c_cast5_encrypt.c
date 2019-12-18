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
typedef  int u32 ;
struct crypto_tfm {int dummy; } ;
struct cast5_ctx {int* Km; int /*<<< orphan*/  rr; int /*<<< orphan*/ * Kr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int F1 (int,int,int /*<<< orphan*/ ) ; 
 int F2 (int,int,int /*<<< orphan*/ ) ; 
 int F3 (int,int,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct cast5_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void cast5_encrypt(struct crypto_tfm *tfm, u8 *outbuf, const u8 *inbuf)
{
	struct cast5_ctx *c = crypto_tfm_ctx(tfm);
	const __be32 *src = (const __be32 *)inbuf;
	__be32 *dst = (__be32 *)outbuf;
	u32 l, r, t;
	u32 I;			/* used by the Fx macros */
	u32 *Km;
	u8 *Kr;

	Km = c->Km;
	Kr = c->Kr;

	/* (L0,R0) <-- (m1...m64).  (Split the plaintext into left and
	 * right 32-bit halves L0 = m1...m32 and R0 = m33...m64.)
	 */
	l = be32_to_cpu(src[0]);
	r = be32_to_cpu(src[1]);

	/* (16 rounds) for i from 1 to 16, compute Li and Ri as follows:
	 *  Li = Ri-1;
	 *  Ri = Li-1 ^ f(Ri-1,Kmi,Kri), where f is defined in Section 2.2
	 * Rounds 1, 4, 7, 10, 13, and 16 use f function Type 1.
	 * Rounds 2, 5, 8, 11, and 14 use f function Type 2.
	 * Rounds 3, 6, 9, 12, and 15 use f function Type 3.
	 */

	if (!(c->rr)) {
		t = l; l = r; r = t ^ F1(r, Km[0], Kr[0]);
		t = l; l = r; r = t ^ F2(r, Km[1], Kr[1]);
		t = l; l = r; r = t ^ F3(r, Km[2], Kr[2]);
		t = l; l = r; r = t ^ F1(r, Km[3], Kr[3]);
		t = l; l = r; r = t ^ F2(r, Km[4], Kr[4]);
		t = l; l = r; r = t ^ F3(r, Km[5], Kr[5]);
		t = l; l = r; r = t ^ F1(r, Km[6], Kr[6]);
		t = l; l = r; r = t ^ F2(r, Km[7], Kr[7]);
		t = l; l = r; r = t ^ F3(r, Km[8], Kr[8]);
		t = l; l = r; r = t ^ F1(r, Km[9], Kr[9]);
		t = l; l = r; r = t ^ F2(r, Km[10], Kr[10]);
		t = l; l = r; r = t ^ F3(r, Km[11], Kr[11]);
		t = l; l = r; r = t ^ F1(r, Km[12], Kr[12]);
		t = l; l = r; r = t ^ F2(r, Km[13], Kr[13]);
		t = l; l = r; r = t ^ F3(r, Km[14], Kr[14]);
		t = l; l = r; r = t ^ F1(r, Km[15], Kr[15]);
	} else {
		t = l; l = r; r = t ^ F1(r, Km[0], Kr[0]);
		t = l; l = r; r = t ^ F2(r, Km[1], Kr[1]);
		t = l; l = r; r = t ^ F3(r, Km[2], Kr[2]);
		t = l; l = r; r = t ^ F1(r, Km[3], Kr[3]);
		t = l; l = r; r = t ^ F2(r, Km[4], Kr[4]);
		t = l; l = r; r = t ^ F3(r, Km[5], Kr[5]);
		t = l; l = r; r = t ^ F1(r, Km[6], Kr[6]);
		t = l; l = r; r = t ^ F2(r, Km[7], Kr[7]);
		t = l; l = r; r = t ^ F3(r, Km[8], Kr[8]);
		t = l; l = r; r = t ^ F1(r, Km[9], Kr[9]);
		t = l; l = r; r = t ^ F2(r, Km[10], Kr[10]);
		t = l; l = r; r = t ^ F3(r, Km[11], Kr[11]);
	}

	/* c1...c64 <-- (R16,L16).  (Exchange final blocks L16, R16 and
	 *  concatenate to form the ciphertext.) */
	dst[0] = cpu_to_be32(r);
	dst[1] = cpu_to_be32(l);
}