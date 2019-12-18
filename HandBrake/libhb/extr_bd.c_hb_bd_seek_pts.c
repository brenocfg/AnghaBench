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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  bd; scalar_t__ next_chap; } ;
typedef  TYPE_1__ hb_bd_t ;

/* Variables and functions */
 scalar_t__ bd_get_current_chapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_seek_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_ts_stream_reset (int /*<<< orphan*/ ) ; 

int hb_bd_seek_pts( hb_bd_t * d, uint64_t pts )
{
    bd_seek_time(d->bd, pts);
    d->next_chap = bd_get_current_chapter( d->bd ) + 1;
    hb_ts_stream_reset(d->stream);
    return 1;
}