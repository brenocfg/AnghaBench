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
struct TYPE_3__ {scalar_t__ decoder; scalar_t__ output_buffer; scalar_t__ input_buffer; scalar_t__ fout; scalar_t__ fin; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */

void init(Context* ctx) {
  ctx->fin = 0;
  ctx->fout = 0;
  ctx->input_buffer = 0;
  ctx->output_buffer = 0;
  ctx->decoder = 0;
}