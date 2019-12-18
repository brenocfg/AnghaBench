#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int skip; int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
typedef  TYPE_2__ ThreadData_convert_frame ;
struct TYPE_10__ {TYPE_1__* internal; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* execute ) (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  PhotosensitivityFrame ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_CELLS ; 
 int /*<<< orphan*/  convert_frame_partial ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void convert_frame(AVFilterContext *ctx, AVFrame *in, PhotosensitivityFrame *out, int skip)
{
    ThreadData_convert_frame td;
    td.in = in;
    td.out = out;
    td.skip = skip;
    ctx->internal->execute(ctx, convert_frame_partial, &td, NULL, FFMIN(NUM_CELLS, ff_filter_get_nb_threads(ctx)));
}