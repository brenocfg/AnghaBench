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
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ VP8Context ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
typedef  int /*<<< orphan*/  VP56Frame ;

/* Variables and functions */
 int /*<<< orphan*/  VP56_FRAME_CURRENT ; 
 int /*<<< orphan*/  VP56_FRAME_GOLDEN ; 
 int /*<<< orphan*/  VP56_FRAME_GOLDEN2 ; 
 int /*<<< orphan*/  VP56_FRAME_NONE ; 
 int /*<<< orphan*/  VP56_FRAME_PREVIOUS ; 
 int vp8_rac_get_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static VP56Frame ref_to_update(VP8Context *s, int update, VP56Frame ref)
{
    VP56RangeCoder *c = &s->c;

    if (update)
        return VP56_FRAME_CURRENT;

    switch (vp8_rac_get_uint(c, 2)) {
    case 1:
        return VP56_FRAME_PREVIOUS;
    case 2:
        return (ref == VP56_FRAME_GOLDEN) ? VP56_FRAME_GOLDEN2 : VP56_FRAME_GOLDEN;
    }
    return VP56_FRAME_NONE;
}