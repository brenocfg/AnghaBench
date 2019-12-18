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
typedef  unsigned int u32 ;
struct ix_sa_dir {unsigned char* npe_ctx; int npe_ctx_idx; unsigned int npe_ctx_phys; int /*<<< orphan*/  npe_mode; } ;
struct ixp_ctx {struct ix_sa_dir decrypt; struct ix_sa_dir encrypt; } ;
struct ix_hash_algo {unsigned int cfgword; int /*<<< orphan*/  icv; } ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  cfgword ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_IPAD_VALUE ; 
 int /*<<< orphan*/  HMAC_OPAD_VALUE ; 
 int /*<<< orphan*/  NPE_OP_HASH_ENABLE ; 
 int /*<<< orphan*/  NPE_OP_HASH_VERIFY ; 
 unsigned int cpu_to_be32 (unsigned int) ; 
 struct ixp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct ix_hash_algo* ix_hash (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int register_chain_var (struct crypto_tfm*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int setup_auth(struct crypto_tfm *tfm, int encrypt, unsigned authsize,
		const u8 *key, int key_len, unsigned digest_len)
{
	u32 itarget, otarget, npe_ctx_addr;
	unsigned char *cinfo;
	int init_len, ret = 0;
	u32 cfgword;
	struct ix_sa_dir *dir;
	struct ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	const struct ix_hash_algo *algo;

	dir = encrypt ? &ctx->encrypt : &ctx->decrypt;
	cinfo = dir->npe_ctx + dir->npe_ctx_idx;
	algo = ix_hash(tfm);

	/* write cfg word to cryptinfo */
	cfgword = algo->cfgword | ( authsize << 6); /* (authsize/4) << 8 */
	*(u32*)cinfo = cpu_to_be32(cfgword);
	cinfo += sizeof(cfgword);

	/* write ICV to cryptinfo */
	memcpy(cinfo, algo->icv, digest_len);
	cinfo += digest_len;

	itarget = dir->npe_ctx_phys + dir->npe_ctx_idx
				+ sizeof(algo->cfgword);
	otarget = itarget + digest_len;
	init_len = cinfo - (dir->npe_ctx + dir->npe_ctx_idx);
	npe_ctx_addr = dir->npe_ctx_phys + dir->npe_ctx_idx;

	dir->npe_ctx_idx += init_len;
	dir->npe_mode |= NPE_OP_HASH_ENABLE;

	if (!encrypt)
		dir->npe_mode |= NPE_OP_HASH_VERIFY;

	ret = register_chain_var(tfm, HMAC_OPAD_VALUE, otarget,
			init_len, npe_ctx_addr, key, key_len);
	if (ret)
		return ret;
	return register_chain_var(tfm, HMAC_IPAD_VALUE, itarget,
			init_len, npe_ctx_addr, key, key_len);
}