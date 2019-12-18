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
struct TYPE_3__ {int /*<<< orphan*/ * ref_index_buf; int /*<<< orphan*/ * motion_val_buf; int /*<<< orphan*/  mb_type_buf; int /*<<< orphan*/  qscale_table_buf; int /*<<< orphan*/  mbskip_table_buf; int /*<<< orphan*/  mb_mean_buf; int /*<<< orphan*/  mc_mb_var_buf; int /*<<< orphan*/  mb_var_buf; scalar_t__ alloc_mb_height; scalar_t__ alloc_mb_width; } ;
typedef  TYPE_1__ Picture ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

void ff_free_picture_tables(Picture *pic)
{
    int i;

    pic->alloc_mb_width  =
    pic->alloc_mb_height = 0;

    av_buffer_unref(&pic->mb_var_buf);
    av_buffer_unref(&pic->mc_mb_var_buf);
    av_buffer_unref(&pic->mb_mean_buf);
    av_buffer_unref(&pic->mbskip_table_buf);
    av_buffer_unref(&pic->qscale_table_buf);
    av_buffer_unref(&pic->mb_type_buf);

    for (i = 0; i < 2; i++) {
        av_buffer_unref(&pic->motion_val_buf[i]);
        av_buffer_unref(&pic->ref_index_buf[i]);
    }
}