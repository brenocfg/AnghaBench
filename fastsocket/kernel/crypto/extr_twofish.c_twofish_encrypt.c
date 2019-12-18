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
struct twofish_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENCCYCLE (int) ; 
 int /*<<< orphan*/  INPACK (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTUNPACK (int,int /*<<< orphan*/ ,int) ; 
 struct twofish_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void twofish_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct twofish_ctx *ctx = crypto_tfm_ctx(tfm);
	const __le32 *src = (const __le32 *)in;
	__le32 *dst = (__le32 *)out;

	/* The four 32-bit chunks of the text. */
	u32 a, b, c, d;
	
	/* Temporaries used by the round function. */
	u32 x, y;

	/* Input whitening and packing. */
	INPACK (0, a, 0);
	INPACK (1, b, 1);
	INPACK (2, c, 2);
	INPACK (3, d, 3);
	
	/* Encryption Feistel cycles. */
	ENCCYCLE (0);
	ENCCYCLE (1);
	ENCCYCLE (2);
	ENCCYCLE (3);
	ENCCYCLE (4);
	ENCCYCLE (5);
	ENCCYCLE (6);
	ENCCYCLE (7);
	
	/* Output whitening and unpacking. */
	OUTUNPACK (0, c, 4);
	OUTUNPACK (1, d, 5);
	OUTUNPACK (2, a, 6);
	OUTUNPACK (3, b, 7);
	
}