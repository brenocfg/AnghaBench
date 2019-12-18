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
typedef  enum AVDurationEstimationMethod { ____Placeholder_AVDurationEstimationMethod } AVDurationEstimationMethod ;

/* Variables and functions */
 char const** duration_name ; 

__attribute__((used)) static const char *duration_estimate_name(enum AVDurationEstimationMethod method)
{
    return duration_name[method];
}