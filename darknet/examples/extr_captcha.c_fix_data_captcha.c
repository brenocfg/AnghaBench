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
struct TYPE_4__ {int rows; int cols; int** vals; } ;
typedef  TYPE_1__ matrix ;
struct TYPE_5__ {TYPE_1__ y; } ;
typedef  TYPE_2__ data ;

/* Variables and functions */
 void* SECRET_NUM ; 

void fix_data_captcha(data d, int mask)
{
    matrix labels = d.y;
    int i, j;
    for(i = 0; i < d.y.rows; ++i){
        for(j = 0; j < d.y.cols; j += 2){
            if (mask){
                if(!labels.vals[i][j]){
                    labels.vals[i][j] = SECRET_NUM;
                    labels.vals[i][j+1] = SECRET_NUM;
                }else if(labels.vals[i][j+1]){
                    labels.vals[i][j] = 0;
                }
            } else{
                if (labels.vals[i][j]) {
                    labels.vals[i][j+1] = 0;
                } else {
                    labels.vals[i][j+1] = 1;
                }
            }
        }
    }
}