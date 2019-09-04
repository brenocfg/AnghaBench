#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mb_x; int slice_height; int mb_y; int msmpeg4_version; int first_slice_line; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_mpeg4_clean_buffers (TYPE_1__*) ; 

void ff_msmpeg4_handle_slices(MpegEncContext *s){
    if (s->mb_x == 0) {
        if (s->slice_height && (s->mb_y % s->slice_height) == 0) {
            if(s->msmpeg4_version < 4){
                ff_mpeg4_clean_buffers(s);
            }
            s->first_slice_line = 1;
        } else {
            s->first_slice_line = 0;
        }
    }
}