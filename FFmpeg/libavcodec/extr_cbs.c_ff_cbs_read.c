#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_1__* codec; } ;
struct TYPE_7__ {int (* split_fragment ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ CodedBitstreamContext ;

/* Variables and functions */
 int cbs_fill_fragment_data (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int cbs_read_fragment_content (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ff_cbs_read(CodedBitstreamContext *ctx,
                CodedBitstreamFragment *frag,
                const uint8_t *data, size_t size)
{
    int err;

    err = cbs_fill_fragment_data(ctx, frag, data, size);
    if (err < 0)
        return err;

    err = ctx->codec->split_fragment(ctx, frag, 0);
    if (err < 0)
        return err;

    return cbs_read_fragment_content(ctx, frag);
}