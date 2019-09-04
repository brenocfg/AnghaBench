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
struct TYPE_3__ {int* group_size; int* group_offset; int* child; int* parent; } ;
typedef  TYPE_1__ tree ;

/* Variables and functions */

int hierarchy_top_prediction(float *predictions, tree *hier, float thresh, int stride)
{
    float p = 1;
    int group = 0;
    int i;
    while(1){
        float max = 0;
        int max_i = 0;

        for(i = 0; i < hier->group_size[group]; ++i){
            int index = i + hier->group_offset[group];
            float val = predictions[(i + hier->group_offset[group])*stride];
            if(val > max){
                max_i = index;
                max = val;
            }
        }
        if(p*max > thresh){
            p = p*max;
            group = hier->child[max_i];
            if(hier->child[max_i] < 0) return max_i;
        } else if (group == 0){
            return max_i;
        } else {
            return hier->parent[hier->group_offset[group]];
        }
    }
    return 0;
}