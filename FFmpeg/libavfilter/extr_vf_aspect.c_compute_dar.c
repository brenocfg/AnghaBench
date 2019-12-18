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
struct TYPE_4__ {int num; int den; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  av_reduce (int*,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void compute_dar(AVRational *dar, AVRational sar, int w, int h)
{
    if (sar.num && sar.den) {
        av_reduce(&dar->num, &dar->den, sar.num * w, sar.den * h, INT_MAX);
    } else {
        av_reduce(&dar->num, &dar->den, w, h, INT_MAX);
    }
}