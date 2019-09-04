#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EDOM ; 
 double INT_MAX ; 
 double INT_MIN ; 
 double SBG_SCALE ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,double) ; 

__attribute__((used)) static inline int scale_double(void *log, double d, double m, int *r)
{
    m *= d * SBG_SCALE;
    if (m < INT_MIN || m >= INT_MAX) {
        if (log)
            av_log(log, AV_LOG_ERROR, "%g is too large\n", d);
        return AVERROR(EDOM);
    }
    *r = m;
    return 0;
}