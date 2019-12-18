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
struct z_stream_s {int dummy; } ;
struct zlib_ctx {struct z_stream_s comp_stream; } ;
struct crypto_pcomp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int Z_OK ; 
 int /*<<< orphan*/  crypto_pcomp_tfm (struct crypto_pcomp*) ; 
 struct zlib_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int zlib_deflateReset (struct z_stream_s*) ; 

__attribute__((used)) static int zlib_compress_init(struct crypto_pcomp *tfm)
{
	int ret;
	struct zlib_ctx *dctx = crypto_tfm_ctx(crypto_pcomp_tfm(tfm));
	struct z_stream_s *stream = &dctx->comp_stream;

	ret = zlib_deflateReset(stream);
	if (ret != Z_OK)
		return -EINVAL;

	return 0;
}