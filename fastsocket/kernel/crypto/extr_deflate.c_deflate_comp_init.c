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
struct deflate_ctx {struct z_stream_s comp_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFLATE_DEF_LEVEL ; 
 int /*<<< orphan*/  DEFLATE_DEF_MEMLEVEL ; 
 int /*<<< orphan*/  DEFLATE_DEF_WINBITS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int Z_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 
 int zlib_deflateInit2 (struct z_stream_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_deflate_workspacesize () ; 

__attribute__((used)) static int deflate_comp_init(struct deflate_ctx *ctx)
{
	int ret = 0;
	struct z_stream_s *stream = &ctx->comp_stream;

	stream->workspace = vmalloc(zlib_deflate_workspacesize());
	if (!stream->workspace ) {
		ret = -ENOMEM;
		goto out;
	}
	memset(stream->workspace, 0, zlib_deflate_workspacesize());
	ret = zlib_deflateInit2(stream, DEFLATE_DEF_LEVEL, Z_DEFLATED,
	                        -DEFLATE_DEF_WINBITS, DEFLATE_DEF_MEMLEVEL,
	                        Z_DEFAULT_STRATEGY);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out_free;
	}
out:	
	return ret;
out_free:
	vfree(stream->workspace);
	goto out;
}