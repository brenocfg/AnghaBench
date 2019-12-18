#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ format; } ;
struct TYPE_10__ {TYPE_3__* work_frames; } ;
struct TYPE_7__ {int /*<<< orphan*/  Locked; } ;
struct TYPE_8__ {TYPE_1__ Data; } ;
struct TYPE_9__ {struct TYPE_9__* next; scalar_t__ used; TYPE_6__* frame; int /*<<< orphan*/  enc_ctrl; TYPE_2__ surface; } ;
typedef  TYPE_3__ QSVFrame ;
typedef  TYPE_4__ QSVEncContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  free_encoder_ctrl_payloads (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_unused_frames(QSVEncContext *q)
{
    QSVFrame *cur = q->work_frames;
    while (cur) {
        if (cur->used && !cur->surface.Data.Locked) {
            free_encoder_ctrl_payloads(&cur->enc_ctrl);
            if (cur->frame->format == AV_PIX_FMT_QSV) {
                av_frame_unref(cur->frame);
            }
            cur->used = 0;
        }
        cur = cur->next;
    }
}