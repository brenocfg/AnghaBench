#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* input_pads; TYPE_3__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  nb_in_active; TYPE_1__* in; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int eof; } ;
typedef  TYPE_3__ ConcatContext ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_input(AVFilterContext *ctx, unsigned in_no)
{
    ConcatContext *cat = ctx->priv;

    cat->in[in_no].eof = 1;
    cat->nb_in_active--;
    av_log(ctx, AV_LOG_VERBOSE, "EOF on %s, %d streams left in segment.\n",
           ctx->input_pads[in_no].name, cat->nb_in_active);
}