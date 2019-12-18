#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int filter_len; int* filter_pos; } ;
struct TYPE_3__ {int filter_len; int* filter_pos; } ;
struct scaler_ctx {int in_width; int out_width; int in_height; int out_height; TYPE_2__ vert; TYPE_1__ horiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool validate_filter(struct scaler_ctx *ctx)
{
   int i;
   int max_h_pos;
   int max_w_pos = ctx->in_width - ctx->horiz.filter_len;

   for (i = 0; i < ctx->out_width; i++)
   {
      if (ctx->horiz.filter_pos[i] > max_w_pos || ctx->horiz.filter_pos[i] < 0)
      {
         fprintf(stderr, "Out X = %d => In X = %d\n", i, ctx->horiz.filter_pos[i]);
         return false;
      }
   }

   max_h_pos = ctx->in_height - ctx->vert.filter_len;

   for (i = 0; i < ctx->out_height; i++)
   {
      if (ctx->vert.filter_pos[i] > max_h_pos || ctx->vert.filter_pos[i] < 0)
      {
         fprintf(stderr, "Out Y = %d => In Y = %d\n", i, ctx->vert.filter_pos[i]);
         return false;
      }
   }

   return true;
}