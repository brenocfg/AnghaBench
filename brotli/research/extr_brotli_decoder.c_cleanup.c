#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fin; scalar_t__ fout; scalar_t__ input_buffer; scalar_t__ output_buffer; scalar_t__ decoder; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliDecoderDestroyInstance (scalar_t__) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void cleanup(Context* ctx) {
  if (ctx->decoder) BrotliDecoderDestroyInstance(ctx->decoder);
  if (ctx->output_buffer) free(ctx->output_buffer);
  if (ctx->input_buffer) free(ctx->input_buffer);
  if (ctx->fout) fclose(ctx->fout);
  if (ctx->fin) fclose(ctx->fin);
}