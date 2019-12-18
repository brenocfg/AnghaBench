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
struct z_stream_s {int /*<<< orphan*/  workspace; } ;
struct deflate_ctx {struct z_stream_s decomp_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFLATE_DEF_WINBITS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int Z_OK ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zlib_inflateInit2 (struct z_stream_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 

__attribute__((used)) static int deflate_decomp_init(struct deflate_ctx *ctx)
{
	int ret = 0;
	struct z_stream_s *stream = &ctx->decomp_stream;

	stream->workspace = kzalloc(zlib_inflate_workspacesize(), GFP_KERNEL);
	if (!stream->workspace ) {
		ret = -ENOMEM;
		goto out;
	}
	ret = zlib_inflateInit2(stream, -DEFLATE_DEF_WINBITS);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out_free;
	}
out:
	return ret;
out_free:
	kfree(stream->workspace);
	goto out;
}