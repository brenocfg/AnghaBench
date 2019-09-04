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
struct TYPE_3__ {int numCB; int dim; scalar_t__ codebook; } ;
typedef  TYPE_1__ elbg_data ;

/* Variables and functions */
 int INT_MAX ; 
 int distance_limited (scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static int get_closest_codebook(elbg_data *elbg, int index)
{
    int i, pick=0, diff, diff_min = INT_MAX;
    for (i=0; i<elbg->numCB; i++)
        if (i != index) {
            diff = distance_limited(elbg->codebook + i*elbg->dim, elbg->codebook + index*elbg->dim, elbg->dim, diff_min);
            if (diff < diff_min) {
                pick = i;
                diff_min = diff;
            }
        }
    return pick;
}