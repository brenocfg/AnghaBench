#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ recording; scalar_t__ playing; } ;
struct TYPE_6__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_8__ {int play_mode; int rec_mode; TYPE_2__ flags; TYPE_1__ ssr; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 scalar_t__ ixj_WriteDSPCommand (int,TYPE_3__*) ; 

__attribute__((used)) static int idle(IXJ *j)
{
	if (ixj_WriteDSPCommand(0x0000, j))		/* DSP Idle */

		return 0;

	if (j->ssr.high || j->ssr.low) {
		return 0;
	} else {
		j->play_mode = -1;
		j->flags.playing = 0;
		j->rec_mode = -1;
		j->flags.recording = 0;
		return 1;
        }
}