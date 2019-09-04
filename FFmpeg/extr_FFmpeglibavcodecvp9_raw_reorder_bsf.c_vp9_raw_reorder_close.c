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
typedef  int /*<<< orphan*/  VP9RawReorderContext ;
struct TYPE_3__ {int /*<<< orphan*/ * priv_data; } ;
typedef  TYPE_1__ AVBSFContext ;

/* Variables and functions */
 int FRAME_SLOTS ; 
 int /*<<< orphan*/  vp9_raw_reorder_clear_slot (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vp9_raw_reorder_close(AVBSFContext *bsf)
{
    VP9RawReorderContext *ctx = bsf->priv_data;
    int s;

    for (s = 0; s < FRAME_SLOTS; s++)
        vp9_raw_reorder_clear_slot(ctx, s);
}