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
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_K (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALC_K192 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALC_K256 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALC_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  CALC_SB192_2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALC_SB256_2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALC_SB_2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/ * calc_sb_tbl ; 
 struct twofish_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/ * q0 ; 
 int /*<<< orphan*/ * q1 ; 
 int w ; 

int twofish_setkey(struct crypto_tfm *tfm, const u8 *key, unsigned int key_len)
{

	struct twofish_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;

	int i, j, k;

	/* Temporaries for CALC_K. */
	u32 x, y;

	/* The S vector used to key the S-boxes, split up into individual bytes.
	 * 128-bit keys use only sa through sh; 256-bit use all of them. */
	u8 sa = 0, sb = 0, sc = 0, sd = 0, se = 0, sf = 0, sg = 0, sh = 0;
	u8 si = 0, sj = 0, sk = 0, sl = 0, sm = 0, sn = 0, so = 0, sp = 0;

	/* Temporary for CALC_S. */
	u8 tmp;

	/* Check key length. */
	if (key_len % 8)
	{
		*flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL; /* unsupported key length */
	}

	/* Compute the first two words of the S vector.  The magic numbers are
	 * the entries of the RS matrix, preprocessed through poly_to_exp. The
	 * numbers in the comments are the original (polynomial form) matrix
	 * entries. */
	CALC_S (sa, sb, sc, sd, 0, 0x00, 0x2D, 0x01, 0x2D); /* 01 A4 02 A4 */
	CALC_S (sa, sb, sc, sd, 1, 0x2D, 0xA4, 0x44, 0x8A); /* A4 56 A1 55 */
	CALC_S (sa, sb, sc, sd, 2, 0x8A, 0xD5, 0xBF, 0xD1); /* 55 82 FC 87 */
	CALC_S (sa, sb, sc, sd, 3, 0xD1, 0x7F, 0x3D, 0x99); /* 87 F3 C1 5A */
	CALC_S (sa, sb, sc, sd, 4, 0x99, 0x46, 0x66, 0x96); /* 5A 1E 47 58 */
	CALC_S (sa, sb, sc, sd, 5, 0x96, 0x3C, 0x5B, 0xED); /* 58 C6 AE DB */
	CALC_S (sa, sb, sc, sd, 6, 0xED, 0x37, 0x4F, 0xE0); /* DB 68 3D 9E */
	CALC_S (sa, sb, sc, sd, 7, 0xE0, 0xD0, 0x8C, 0x17); /* 9E E5 19 03 */
	CALC_S (se, sf, sg, sh, 8, 0x00, 0x2D, 0x01, 0x2D); /* 01 A4 02 A4 */
	CALC_S (se, sf, sg, sh, 9, 0x2D, 0xA4, 0x44, 0x8A); /* A4 56 A1 55 */
	CALC_S (se, sf, sg, sh, 10, 0x8A, 0xD5, 0xBF, 0xD1); /* 55 82 FC 87 */
	CALC_S (se, sf, sg, sh, 11, 0xD1, 0x7F, 0x3D, 0x99); /* 87 F3 C1 5A */
	CALC_S (se, sf, sg, sh, 12, 0x99, 0x46, 0x66, 0x96); /* 5A 1E 47 58 */
	CALC_S (se, sf, sg, sh, 13, 0x96, 0x3C, 0x5B, 0xED); /* 58 C6 AE DB */
	CALC_S (se, sf, sg, sh, 14, 0xED, 0x37, 0x4F, 0xE0); /* DB 68 3D 9E */
	CALC_S (se, sf, sg, sh, 15, 0xE0, 0xD0, 0x8C, 0x17); /* 9E E5 19 03 */

	if (key_len == 24 || key_len == 32) { /* 192- or 256-bit key */
		/* Calculate the third word of the S vector */
		CALC_S (si, sj, sk, sl, 16, 0x00, 0x2D, 0x01, 0x2D); /* 01 A4 02 A4 */
		CALC_S (si, sj, sk, sl, 17, 0x2D, 0xA4, 0x44, 0x8A); /* A4 56 A1 55 */
		CALC_S (si, sj, sk, sl, 18, 0x8A, 0xD5, 0xBF, 0xD1); /* 55 82 FC 87 */
		CALC_S (si, sj, sk, sl, 19, 0xD1, 0x7F, 0x3D, 0x99); /* 87 F3 C1 5A */
		CALC_S (si, sj, sk, sl, 20, 0x99, 0x46, 0x66, 0x96); /* 5A 1E 47 58 */
		CALC_S (si, sj, sk, sl, 21, 0x96, 0x3C, 0x5B, 0xED); /* 58 C6 AE DB */
		CALC_S (si, sj, sk, sl, 22, 0xED, 0x37, 0x4F, 0xE0); /* DB 68 3D 9E */
		CALC_S (si, sj, sk, sl, 23, 0xE0, 0xD0, 0x8C, 0x17); /* 9E E5 19 03 */
	}

	if (key_len == 32) { /* 256-bit key */
		/* Calculate the fourth word of the S vector */
		CALC_S (sm, sn, so, sp, 24, 0x00, 0x2D, 0x01, 0x2D); /* 01 A4 02 A4 */
		CALC_S (sm, sn, so, sp, 25, 0x2D, 0xA4, 0x44, 0x8A); /* A4 56 A1 55 */
		CALC_S (sm, sn, so, sp, 26, 0x8A, 0xD5, 0xBF, 0xD1); /* 55 82 FC 87 */
		CALC_S (sm, sn, so, sp, 27, 0xD1, 0x7F, 0x3D, 0x99); /* 87 F3 C1 5A */
		CALC_S (sm, sn, so, sp, 28, 0x99, 0x46, 0x66, 0x96); /* 5A 1E 47 58 */
		CALC_S (sm, sn, so, sp, 29, 0x96, 0x3C, 0x5B, 0xED); /* 58 C6 AE DB */
		CALC_S (sm, sn, so, sp, 30, 0xED, 0x37, 0x4F, 0xE0); /* DB 68 3D 9E */
		CALC_S (sm, sn, so, sp, 31, 0xE0, 0xD0, 0x8C, 0x17); /* 9E E5 19 03 */

		/* Compute the S-boxes. */
		for ( i = j = 0, k = 1; i < 256; i++, j += 2, k += 2 ) {
			CALC_SB256_2( i, calc_sb_tbl[j], calc_sb_tbl[k] );
		}

		/* CALC_K256/CALC_K192/CALC_K loops were unrolled.
		 * Unrolling produced x2.5 more code (+18k on i386),
		 * and speeded up key setup by 7%:
		 * unrolled: twofish_setkey/sec: 41128
		 *     loop: twofish_setkey/sec: 38148
		 * CALC_K256: ~100 insns each
		 * CALC_K192: ~90 insns
		 *    CALC_K: ~70 insns
		 */
		/* Calculate whitening and round subkeys */
		for ( i = 0; i < 8; i += 2 ) {
			CALC_K256 (w, i, q0[i], q1[i], q0[i+1], q1[i+1]);
		}
		for ( i = 0; i < 32; i += 2 ) {
			CALC_K256 (k, i, q0[i+8], q1[i+8], q0[i+9], q1[i+9]);
		}
	} else if (key_len == 24) { /* 192-bit key */
		/* Compute the S-boxes. */
		for ( i = j = 0, k = 1; i < 256; i++, j += 2, k += 2 ) {
		        CALC_SB192_2( i, calc_sb_tbl[j], calc_sb_tbl[k] );
		}

		/* Calculate whitening and round subkeys */
		for ( i = 0; i < 8; i += 2 ) {
			CALC_K192 (w, i, q0[i], q1[i], q0[i+1], q1[i+1]);
		}
		for ( i = 0; i < 32; i += 2 ) {
			CALC_K192 (k, i, q0[i+8], q1[i+8], q0[i+9], q1[i+9]);
		}
	} else { /* 128-bit key */
		/* Compute the S-boxes. */
		for ( i = j = 0, k = 1; i < 256; i++, j += 2, k += 2 ) {
			CALC_SB_2( i, calc_sb_tbl[j], calc_sb_tbl[k] );
		}

		/* Calculate whitening and round subkeys */
		for ( i = 0; i < 8; i += 2 ) {
			CALC_K (w, i, q0[i], q1[i], q0[i+1], q1[i+1]);
		}
		for ( i = 0; i < 32; i += 2 ) {
			CALC_K (k, i, q0[i+8], q1[i+8], q0[i+9], q1[i+9]);
		}
	}

	return 0;
}