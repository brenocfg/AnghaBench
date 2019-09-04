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
struct TYPE_3__ {int pict_type; int /*<<< orphan*/  b_code; int /*<<< orphan*/  f_code; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
#define  AV_PICTURE_TYPE_B 131 
#define  AV_PICTURE_TYPE_I 130 
#define  AV_PICTURE_TYPE_P 129 
#define  AV_PICTURE_TYPE_S 128 
 int /*<<< orphan*/  FFMAX3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ff_mpeg4_get_video_packet_prefix_length(MpegEncContext *s)
{
    switch (s->pict_type) {
    case AV_PICTURE_TYPE_I:
        return 16;
    case AV_PICTURE_TYPE_P:
    case AV_PICTURE_TYPE_S:
        return s->f_code + 15;
    case AV_PICTURE_TYPE_B:
        return FFMAX3(s->f_code, s->b_code, 2) + 15;
    default:
        return -1;
    }
}