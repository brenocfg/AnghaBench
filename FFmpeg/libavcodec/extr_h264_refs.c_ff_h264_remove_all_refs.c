#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* f; } ;
struct TYPE_11__ {scalar_t__ long_ref_count; int short_ref_count; int /*<<< orphan*/  default_ref; int /*<<< orphan*/ ** short_ref; TYPE_6__ last_pic_for_ec; } ;
struct TYPE_10__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ff_h264_ref_picture (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h264_unref_picture (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_long (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreference_pic (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ff_h264_remove_all_refs(H264Context *h)
{
    int i;

    for (i = 0; i < 16; i++) {
        remove_long(h, i, 0);
    }
    assert(h->long_ref_count == 0);

    if (h->short_ref_count && !h->last_pic_for_ec.f->data[0]) {
        ff_h264_unref_picture(h, &h->last_pic_for_ec);
        ff_h264_ref_picture(h, &h->last_pic_for_ec, h->short_ref[0]);
    }

    for (i = 0; i < h->short_ref_count; i++) {
        unreference_pic(h, h->short_ref[i], 0);
        h->short_ref[i] = NULL;
    }
    h->short_ref_count = 0;

    memset(h->default_ref, 0, sizeof(h->default_ref));
}