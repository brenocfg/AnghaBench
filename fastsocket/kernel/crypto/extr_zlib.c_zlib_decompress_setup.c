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
struct z_stream_s {int /*<<< orphan*/ * workspace; } ;
struct zlib_ctx {int /*<<< orphan*/  decomp_windowBits; struct z_stream_s decomp_stream; } ;
struct nlattr {int dummy; } ;
struct crypto_pcomp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_WBITS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ZLIB_DECOMP_MAX ; 
 size_t ZLIB_DECOMP_WINDOWBITS ; 
 int Z_OK ; 
 int /*<<< orphan*/  crypto_pcomp_tfm (struct crypto_pcomp*) ; 
 struct zlib_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_parse (struct nlattr**,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zlib_decomp_exit (struct zlib_ctx*) ; 
 int zlib_inflateInit2 (struct z_stream_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 

__attribute__((used)) static int zlib_decompress_setup(struct crypto_pcomp *tfm, void *params,
				 unsigned int len)
{
	struct zlib_ctx *ctx = crypto_tfm_ctx(crypto_pcomp_tfm(tfm));
	struct z_stream_s *stream = &ctx->decomp_stream;
	struct nlattr *tb[ZLIB_DECOMP_MAX + 1];
	int ret = 0;

	ret = nla_parse(tb, ZLIB_DECOMP_MAX, params, len, NULL);
	if (ret)
		return ret;

	zlib_decomp_exit(ctx);

	ctx->decomp_windowBits = tb[ZLIB_DECOMP_WINDOWBITS]
				 ? nla_get_u32(tb[ZLIB_DECOMP_WINDOWBITS])
				 : DEF_WBITS;

	stream->workspace = kzalloc(zlib_inflate_workspacesize(), GFP_KERNEL);
	if (!stream->workspace)
		return -ENOMEM;

	ret = zlib_inflateInit2(stream, ctx->decomp_windowBits);
	if (ret != Z_OK) {
		kfree(stream->workspace);
		stream->workspace = NULL;
		return -EINVAL;
	}

	return 0;
}