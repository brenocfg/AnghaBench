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
struct TYPE_3__ {scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int /*<<< orphan*/  AV_RB32 (scalar_t__) ; 
 scalar_t__ AV_RL32 (scalar_t__) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 double av_int2float (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (double) ; 

__attribute__((used)) static int thp_probe(const AVProbeData *p)
{
    double d;
    /* check file header */
    if (AV_RL32(p->buf) != MKTAG('T', 'H', 'P', '\0'))
        return 0;

    d = av_int2float(AV_RB32(p->buf + 16));
    if (d < 0.1 || d > 1000 || isnan(d))
        return AVPROBE_SCORE_MAX/4;

    return AVPROBE_SCORE_MAX;
}