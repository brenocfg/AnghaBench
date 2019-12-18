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
struct TYPE_4__ {int out; int in; int flen; int /*<<< orphan*/ ** fifo; } ;
struct TYPE_5__ {TYPE_1__ mf; } ;
typedef  TYPE_2__ hb_track_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */

__attribute__((used)) static hb_buffer_t *mf_peek( hb_track_t *track )
{
    return track->mf.out == track->mf.in ?
                NULL : track->mf.fifo[track->mf.out & (track->mf.flen - 1)];
}