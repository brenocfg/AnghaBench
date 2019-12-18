#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int mb_height; TYPE_1__* avctx; } ;
struct TYPE_9__ {int reference; TYPE_2__* parent; } ;
struct TYPE_8__ {int field_picture; int /*<<< orphan*/  tf; } ;
struct TYPE_7__ {int active_thread_type; } ;
typedef  TYPE_3__ H264Ref ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int FF_THREAD_FRAME ; 
 int /*<<< orphan*/  HAVE_THREADS ; 
 int /*<<< orphan*/  ff_thread_await_progress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void await_reference_mb_row(const H264Context *const h, H264Ref *ref,
                                   int mb_y)
{
    int ref_field         = ref->reference - 1;
    int ref_field_picture = ref->parent->field_picture;
    int ref_height        = 16 * h->mb_height >> ref_field_picture;

    if (!HAVE_THREADS || !(h->avctx->active_thread_type & FF_THREAD_FRAME))
        return;

    /* FIXME: It can be safe to access mb stuff
     * even if pixels aren't deblocked yet. */

    ff_thread_await_progress(&ref->parent->tf,
                             FFMIN(16 * mb_y >> ref_field_picture,
                                   ref_height - 1),
                             ref_field_picture && ref_field);
}