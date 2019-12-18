#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* DPB; } ;
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_3__ H264Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int H264_MAX_PICTURE_COUNT ; 

__attribute__((used)) static int find_unused_picture(H264Context *h)
{
    int i;

    for (i = 0; i < H264_MAX_PICTURE_COUNT; i++) {
        if (!h->DPB[i].f->buf[0])
            return i;
    }
    return AVERROR_INVALIDDATA;
}