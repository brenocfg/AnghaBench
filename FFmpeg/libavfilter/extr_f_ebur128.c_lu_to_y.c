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
struct TYPE_4__ {double h; } ;
struct TYPE_5__ {int meter; double scale_range; TYPE_1__ graph; } ;
typedef  TYPE_2__ EBUR128Context ;

/* Variables and functions */
 double av_clipf (double,int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static inline int lu_to_y(const EBUR128Context *ebur128, double v)
{
    v += 2 * ebur128->meter;                            // make it in range [0;...]
    v  = av_clipf(v, 0, ebur128->scale_range);          // make sure it's in the graph scale
    v  = ebur128->scale_range - v;                      // invert value (y=0 is on top)
    return v * ebur128->graph.h / ebur128->scale_range; // rescale from scale range to px height
}