#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ curr_frame_offset; } ;
struct TYPE_8__ {TYPE_1__ abs_motion; } ;
struct TYPE_7__ {scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_2__ IterIndices ;
typedef  TYPE_3__ DeshakeOpenCLContext ;

/* Variables and functions */

__attribute__((used)) static IterIndices start_end_for(DeshakeOpenCLContext *deshake_ctx, int length) {
    IterIndices indices;

    indices.start = deshake_ctx->abs_motion.curr_frame_offset - (length / 2);
    indices.end = deshake_ctx->abs_motion.curr_frame_offset + (length / 2) + (length % 2);

    return indices;
}