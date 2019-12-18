#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* ctx; } ;
struct TYPE_9__ {scalar_t__* format; } ;
struct TYPE_11__ {int /*<<< orphan*/  filename; } ;
struct TYPE_12__ {TYPE_2__ muxer; TYPE_1__ config; TYPE_3__ params; } ;
typedef  TYPE_4__ ffmpeg_t ;
struct TYPE_13__ {int /*<<< orphan*/ * filename; int /*<<< orphan*/  pb; void* oformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  av_free (TYPE_6__*) ; 
 void* av_guess_format (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* avformat_alloc_context () ; 
 scalar_t__ avio_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* ctx ; 

__attribute__((used)) static bool ffmpeg_init_muxer_pre(ffmpeg_t *handle)
{
   ctx = avformat_alloc_context();
   av_strlcpy(ctx->filename, handle->params.filename, sizeof(ctx->filename));

   if (*handle->config.format)
      ctx->oformat = av_guess_format(handle->config.format, NULL, NULL);
   else
      ctx->oformat = av_guess_format(NULL, ctx->filename, NULL);

   if (!ctx->oformat)
      return false;

   if (avio_open(&ctx->pb, ctx->filename, AVIO_FLAG_WRITE) < 0)
   {
      av_free(ctx);
      return false;
   }

   handle->muxer.ctx = ctx;
   return true;
}