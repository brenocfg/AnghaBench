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
struct TYPE_4__ {int cols; int rows; float** vals; } ;
struct TYPE_5__ {TYPE_1__ y; } ;
typedef  TYPE_2__ data ;

/* Variables and functions */

void smooth_data(data d)
{
    int i, j;
    float scale = 1. / d.y.cols;
    float eps = .1;
    for(i = 0; i < d.y.rows; ++i){
        for(j = 0; j < d.y.cols; ++j){
            d.y.vals[i][j] = eps * scale + (1-eps) * d.y.vals[i][j];
        }
    }
}