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
struct TYPE_4__ {int c; int h; int w; float* data; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */

void smooth(image recon, image update, float lambda, int num)
{
    int i, j, k;
    int ii, jj;
    for(k = 0; k < recon.c; ++k){
        for(j = 0; j < recon.h; ++j){
            for(i = 0; i < recon.w; ++i){
                int out_index = i + recon.w*(j + recon.h*k);
                for(jj = j-num; jj <= j + num && jj < recon.h; ++jj){
                    if (jj < 0) continue;
                    for(ii = i-num; ii <= i + num && ii < recon.w; ++ii){
                        if (ii < 0) continue;
                        int in_index = ii + recon.w*(jj + recon.h*k);
                        update.data[out_index] += lambda * (recon.data[in_index] - recon.data[out_index]);
                    }
                }
            }
        }
    }
}