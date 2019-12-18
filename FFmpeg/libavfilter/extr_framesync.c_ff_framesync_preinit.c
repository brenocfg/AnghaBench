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
struct TYPE_4__ {int /*<<< orphan*/ * class; } ;
typedef  TYPE_1__ FFFrameSync ;

/* Variables and functions */
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_1__*) ; 
 int /*<<< orphan*/  framesync_class ; 

void ff_framesync_preinit(FFFrameSync *fs)
{
    if (fs->class)
        return;
    fs->class  = &framesync_class;
    av_opt_set_defaults(fs);
}