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
struct TYPE_8__ {int /*<<< orphan*/  long_ref_count; TYPE_1__** long_ref; } ;
struct TYPE_7__ {int long_ref; } ;
typedef  TYPE_1__ H264Picture ;
typedef  TYPE_2__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unreference_pic (TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static H264Picture *remove_long(H264Context *h, int i, int ref_mask)
{
    H264Picture *pic;

    pic = h->long_ref[i];
    if (pic) {
        if (unreference_pic(h, pic, ref_mask)) {
            assert(h->long_ref[i]->long_ref == 1);
            h->long_ref[i]->long_ref = 0;
            h->long_ref[i]           = NULL;
            h->long_ref_count--;
        }
    }

    return pic;
}