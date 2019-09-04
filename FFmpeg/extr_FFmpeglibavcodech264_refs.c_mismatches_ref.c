#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
struct TYPE_11__ {TYPE_2__* cur_pic_ptr; } ;
struct TYPE_10__ {TYPE_5__* f; } ;
struct TYPE_9__ {TYPE_1__* f; } ;
struct TYPE_8__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
typedef  TYPE_3__ H264Picture ;
typedef  TYPE_4__ H264Context ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static int mismatches_ref(const H264Context *h, const H264Picture *pic)
{
    const AVFrame *f = pic->f;
    return (h->cur_pic_ptr->f->width  != f->width ||
            h->cur_pic_ptr->f->height != f->height ||
            h->cur_pic_ptr->f->format != f->format);
}