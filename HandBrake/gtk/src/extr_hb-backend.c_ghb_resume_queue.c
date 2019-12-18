#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_STATE_PAUSED ; 
 int /*<<< orphan*/  h_queue ; 
 int /*<<< orphan*/  hb_resume (int /*<<< orphan*/ ) ; 
 TYPE_2__ hb_status ; 

void
ghb_resume_queue()
{
    hb_status.queue.state &= ~GHB_STATE_PAUSED;
    hb_resume( h_queue );
}