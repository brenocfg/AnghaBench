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
struct TYPE_8__ {TYPE_1__* par_out; TYPE_2__* par_in; } ;
struct TYPE_7__ {int /*<<< orphan*/  extradata_size; scalar_t__ extradata; } ;
struct TYPE_6__ {char* extradata; } ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scan_buffer (scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpeg4_unpack_bframes_init(AVBSFContext *ctx)
{
    if (ctx->par_in->extradata) {
        int pos_p_ext = -1;
        scan_buffer(ctx->par_in->extradata, ctx->par_in->extradata_size, &pos_p_ext, NULL, NULL);
        if (pos_p_ext >= 0) {
            av_log(ctx, AV_LOG_DEBUG,
                   "Updating DivX userdata (remove trailing 'p') in extradata.\n");
            ctx->par_out->extradata[pos_p_ext] = '\0';
        }
    }

    return 0;
}