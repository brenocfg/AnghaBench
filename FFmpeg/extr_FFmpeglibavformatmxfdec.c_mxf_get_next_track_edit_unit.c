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
typedef  int int64_t ;
struct TYPE_3__ {scalar_t__ original_duration; int /*<<< orphan*/  edit_rate; int /*<<< orphan*/  index_sid; } ;
typedef  TYPE_1__ MXFTrack ;
typedef  int /*<<< orphan*/  MXFIndexTable ;
typedef  int /*<<< orphan*/  MXFContext ;

/* Variables and functions */
 scalar_t__ mxf_edit_unit_absolute_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mxf_find_index_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxf_get_next_track_edit_unit(MXFContext *mxf, MXFTrack *track, int64_t current_offset, int64_t *edit_unit_out)
{
    int64_t a, b, m, offset;
    MXFIndexTable *t = mxf_find_index_table(mxf, track->index_sid);

    if (!t || track->original_duration <= 0)
        return -1;

    a = -1;
    b = track->original_duration;

    while (b - a > 1) {
        m = (a + b) >> 1;
        if (mxf_edit_unit_absolute_offset(mxf, t, m, track->edit_rate, NULL, &offset, NULL, 0) < 0)
            return -1;
        if (offset < current_offset)
            a = m;
        else
            b = m;
    }

    *edit_unit_out = b;

    return 0;
}