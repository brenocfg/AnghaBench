#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int nb_in; unsigned int sync_level; TYPE_1__* in; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  sync; } ;
typedef  TYPE_2__ FFFrameSync ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 unsigned int FFMAX (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_EOF ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  framesync_eof (TYPE_2__*) ; 

__attribute__((used)) static void framesync_sync_level_update(FFFrameSync *fs)
{
    unsigned i, level = 0;

    for (i = 0; i < fs->nb_in; i++)
        if (fs->in[i].state != STATE_EOF)
            level = FFMAX(level, fs->in[i].sync);
    av_assert0(level <= fs->sync_level);
    if (level < fs->sync_level)
        av_log(fs, AV_LOG_VERBOSE, "Sync level %u\n", level);
    if (level)
        fs->sync_level = level;
    else
        framesync_eof(fs);
}