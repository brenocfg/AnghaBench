#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ stride; int /*<<< orphan*/ * frame; } ;
struct TYPE_9__ {scalar_t__ stride; int /*<<< orphan*/ * frame; } ;
struct TYPE_8__ {scalar_t__ stride; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * frame; } ;
struct TYPE_7__ {int /*<<< orphan*/ * filter_pos; scalar_t__ filter_stride; scalar_t__ filter_len; int /*<<< orphan*/ * filter; } ;
struct TYPE_6__ {int /*<<< orphan*/ * filter_pos; scalar_t__ filter_stride; scalar_t__ filter_len; int /*<<< orphan*/ * filter; } ;
struct scaler_ctx {TYPE_5__ output; TYPE_4__ input; TYPE_3__ scaled; TYPE_2__ vert; TYPE_1__ horiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void scaler_ctx_gen_reset(struct scaler_ctx *ctx)
{
   if (ctx->horiz.filter)
      free(ctx->horiz.filter);
   if (ctx->horiz.filter_pos)
      free(ctx->horiz.filter_pos);
   if (ctx->vert.filter)
      free(ctx->vert.filter);
   if (ctx->vert.filter_pos)
      free(ctx->vert.filter_pos);
   if (ctx->scaled.frame)
      free(ctx->scaled.frame);
   if (ctx->input.frame)
      free(ctx->input.frame);
   if (ctx->output.frame)
      free(ctx->output.frame);

   ctx->horiz.filter        = NULL;
   ctx->horiz.filter_len    = 0;
   ctx->horiz.filter_stride = 0;
   ctx->horiz.filter_pos    = NULL;

   ctx->vert.filter         = NULL;
   ctx->vert.filter_len     = 0;
   ctx->vert.filter_stride  = 0;
   ctx->vert.filter_pos     = NULL;

   ctx->scaled.frame        = NULL;
   ctx->scaled.width        = 0;
   ctx->scaled.height       = 0;
   ctx->scaled.stride       = 0;

   ctx->input.frame         = NULL;
   ctx->input.stride        = 0;

   ctx->output.frame        = NULL;
   ctx->output.stride       = 0;
}