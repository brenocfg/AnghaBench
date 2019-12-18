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
struct TYPE_3__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ VDPAUPixFmtMap ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_NONE ; 

__attribute__((used)) static int count_pixfmts(const VDPAUPixFmtMap *map)
{
    int count = 0;
    while (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        count++;
    }
    return count;
}