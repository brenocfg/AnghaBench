#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int eof; TYPE_1__* parent; scalar_t__ frame_ready; } ;
struct TYPE_4__ {int /*<<< orphan*/ * outputs; } ;
typedef  TYPE_2__ FFFrameSync ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR_EOF ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void framesync_eof(FFFrameSync *fs)
{
    fs->eof = 1;
    fs->frame_ready = 0;
    ff_outlink_set_status(fs->parent->outputs[0], AVERROR_EOF, AV_NOPTS_VALUE);
}