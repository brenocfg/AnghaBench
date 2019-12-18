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
struct z_stream_s {int avail_out; int /*<<< orphan*/  next_out; int /*<<< orphan*/  avail_in; int /*<<< orphan*/  next_in; } ;
struct zlib_ctx {struct z_stream_s comp_stream; } ;
struct crypto_pcomp {int dummy; } ;
struct comp_request {int avail_out; int /*<<< orphan*/  next_out; int /*<<< orphan*/  avail_in; int /*<<< orphan*/  next_in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  crypto_pcomp_tfm (struct crypto_pcomp*) ; 
 struct zlib_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int zlib_deflate (struct z_stream_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zlib_compress_final(struct crypto_pcomp *tfm,
			       struct comp_request *req)
{
	int ret;
	struct zlib_ctx *dctx = crypto_tfm_ctx(crypto_pcomp_tfm(tfm));
	struct z_stream_s *stream = &dctx->comp_stream;

	pr_debug("avail_in %u, avail_out %u\n", req->avail_in, req->avail_out);
	stream->next_in = req->next_in;
	stream->avail_in = req->avail_in;
	stream->next_out = req->next_out;
	stream->avail_out = req->avail_out;

	ret = zlib_deflate(stream, Z_FINISH);
	if (ret != Z_STREAM_END) {
		pr_debug("zlib_deflate failed %d\n", ret);
		return -EINVAL;
	}

	ret = req->avail_out - stream->avail_out;
	pr_debug("avail_in %u, avail_out %u (consumed %u, produced %u)\n",
		 stream->avail_in, stream->avail_out,
		 req->avail_in - stream->avail_in, ret);
	req->next_in = stream->next_in;
	req->avail_in = stream->avail_in;
	req->next_out = stream->next_out;
	req->avail_out = stream->avail_out;
	return ret;
}