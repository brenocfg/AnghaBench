#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pict_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_type; int /*<<< orphan*/  p_frame_skipped; TYPE_2__ s; } ;
typedef  TYPE_1__ VC1Context ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
#define  AV_PICTURE_TYPE_B 130 
#define  AV_PICTURE_TYPE_I 129 
#define  AV_PICTURE_TYPE_P 128 

__attribute__((used)) static int vc1_get_PTYPE(const VC1Context *v)
{
    const MpegEncContext *s = &v->s;
    switch (s->pict_type) {
    case AV_PICTURE_TYPE_I: return 0;
    case AV_PICTURE_TYPE_P: return v->p_frame_skipped ? 4 : 1;
    case AV_PICTURE_TYPE_B: return v->bi_type         ? 3 : 2;
    }
    return 0;
}