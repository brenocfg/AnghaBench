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
struct zlib_ctx {struct z_stream_s decomp_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zlib_inflateEnd (struct z_stream_s*) ; 

__attribute__((used)) static void zlib_decomp_exit(struct zlib_ctx *ctx)
{
	struct z_stream_s *stream = &ctx->decomp_stream;

	if (stream->workspace) {
		zlib_inflateEnd(stream);
		kfree(stream->workspace);
		stream->workspace = NULL;
	}
}