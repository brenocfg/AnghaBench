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
struct TYPE_3__ {int /*<<< orphan*/  f; int /*<<< orphan*/  mb_type_buf; int /*<<< orphan*/ * ref_index_buf; int /*<<< orphan*/ * motion_val_buf; } ;
typedef  TYPE_1__ SVQ3Frame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_picture(AVCodecContext *avctx, SVQ3Frame *pic)
{
    int i;
    for (i = 0; i < 2; i++) {
        av_buffer_unref(&pic->motion_val_buf[i]);
        av_buffer_unref(&pic->ref_index_buf[i]);
    }
    av_buffer_unref(&pic->mb_type_buf);

    av_frame_unref(pic->f);
}