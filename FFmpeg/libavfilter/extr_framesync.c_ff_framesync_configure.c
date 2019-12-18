#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_9__ {scalar_t__ opt_eof_action; int opt_shortest; unsigned int nb_in; int /*<<< orphan*/  sync_level; TYPE_2__* in; TYPE_1__ time_base; scalar_t__ opt_repeatlast; } ;
struct TYPE_8__ {int /*<<< orphan*/  pts_next; int /*<<< orphan*/  pts; TYPE_1__ time_base; scalar_t__ sync; int /*<<< orphan*/  after; } ;
typedef  TYPE_3__ FFFrameSync ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ EOF_ACTION_ENDALL ; 
 scalar_t__ EOF_ACTION_PASS ; 
 int /*<<< orphan*/  EXT_NULL ; 
 int /*<<< orphan*/  EXT_STOP ; 
 int /*<<< orphan*/  UINT_MAX ; 
 void* av_gcd (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  framesync_sync_level_update (TYPE_3__*) ; 

int ff_framesync_configure(FFFrameSync *fs)
{
    unsigned i;
    int64_t gcd, lcm;

    if (!fs->opt_repeatlast || fs->opt_eof_action == EOF_ACTION_PASS) {
        fs->opt_repeatlast = 0;
        fs->opt_eof_action = EOF_ACTION_PASS;
    }
    if (fs->opt_shortest || fs->opt_eof_action == EOF_ACTION_ENDALL) {
        fs->opt_shortest = 1;
        fs->opt_eof_action = EOF_ACTION_ENDALL;
    }
    if (!fs->opt_repeatlast) {
        for (i = 1; i < fs->nb_in; i++) {
            fs->in[i].after = EXT_NULL;
            fs->in[i].sync  = 0;
        }
    }
    if (fs->opt_shortest) {
        for (i = 0; i < fs->nb_in; i++)
            fs->in[i].after = EXT_STOP;
    }

    if (!fs->time_base.num) {
        for (i = 0; i < fs->nb_in; i++) {
            if (fs->in[i].sync) {
                if (fs->time_base.num) {
                    gcd = av_gcd(fs->time_base.den, fs->in[i].time_base.den);
                    lcm = (fs->time_base.den / gcd) * fs->in[i].time_base.den;
                    if (lcm < AV_TIME_BASE / 2) {
                        fs->time_base.den = lcm;
                        fs->time_base.num = av_gcd(fs->time_base.num,
                                                   fs->in[i].time_base.num);
                    } else {
                        fs->time_base.num = 1;
                        fs->time_base.den = AV_TIME_BASE;
                        break;
                    }
                } else {
                    fs->time_base = fs->in[i].time_base;
                }
            }
        }
        if (!fs->time_base.num) {
            av_log(fs, AV_LOG_ERROR, "Impossible to set time base\n");
            return AVERROR(EINVAL);
        }
        av_log(fs, AV_LOG_VERBOSE, "Selected %d/%d time base\n",
               fs->time_base.num, fs->time_base.den);
    }

    for (i = 0; i < fs->nb_in; i++)
        fs->in[i].pts = fs->in[i].pts_next = AV_NOPTS_VALUE;
    fs->sync_level = UINT_MAX;
    framesync_sync_level_update(fs);

    return 0;
}