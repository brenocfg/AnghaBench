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
struct zlib_ctx {struct z_stream_s comp_stream; } ;
struct nlattr {int dummy; } ;
struct crypto_pcomp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_MEM_LEVEL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 size_t ZLIB_COMP_LEVEL ; 
 int /*<<< orphan*/  ZLIB_COMP_MAX ; 
 size_t ZLIB_COMP_MEMLEVEL ; 
 size_t ZLIB_COMP_METHOD ; 
 size_t ZLIB_COMP_STRATEGY ; 
 size_t ZLIB_COMP_WINDOWBITS ; 
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int Z_OK ; 
 int /*<<< orphan*/  crypto_pcomp_tfm (struct crypto_pcomp*) ; 
 struct zlib_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_parse (struct nlattr**,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (size_t) ; 
 int /*<<< orphan*/  zlib_comp_exit (struct zlib_ctx*) ; 
 int zlib_deflateInit2 (struct z_stream_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t zlib_deflate_workspacesize () ; 

__attribute__((used)) static int zlib_compress_setup(struct crypto_pcomp *tfm, void *params,
			       unsigned int len)
{
	struct zlib_ctx *ctx = crypto_tfm_ctx(crypto_pcomp_tfm(tfm));
	struct z_stream_s *stream = &ctx->comp_stream;
	struct nlattr *tb[ZLIB_COMP_MAX + 1];
	size_t workspacesize;
	int ret;

	ret = nla_parse(tb, ZLIB_COMP_MAX, params, len, NULL);
	if (ret)
		return ret;

	zlib_comp_exit(ctx);

	workspacesize = zlib_deflate_workspacesize();
	stream->workspace = vmalloc(workspacesize);
	if (!stream->workspace)
		return -ENOMEM;

	memset(stream->workspace, 0, workspacesize);
	ret = zlib_deflateInit2(stream,
				tb[ZLIB_COMP_LEVEL]
					? nla_get_u32(tb[ZLIB_COMP_LEVEL])
					: Z_DEFAULT_COMPRESSION,
				tb[ZLIB_COMP_METHOD]
					? nla_get_u32(tb[ZLIB_COMP_METHOD])
					: Z_DEFLATED,
				tb[ZLIB_COMP_WINDOWBITS]
					? nla_get_u32(tb[ZLIB_COMP_WINDOWBITS])
					: MAX_WBITS,
				tb[ZLIB_COMP_MEMLEVEL]
					? nla_get_u32(tb[ZLIB_COMP_MEMLEVEL])
					: DEF_MEM_LEVEL,
				tb[ZLIB_COMP_STRATEGY]
					? nla_get_u32(tb[ZLIB_COMP_STRATEGY])
					: Z_DEFAULT_STRATEGY);
	if (ret != Z_OK) {
		vfree(stream->workspace);
		stream->workspace = NULL;
		return -EINVAL;
	}

	return 0;
}