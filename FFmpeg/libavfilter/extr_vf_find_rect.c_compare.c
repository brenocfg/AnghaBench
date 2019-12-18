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
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_4__ {int height; int width; int** data; int* linesize; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 float fabs (float) ; 
 int sqrt (int) ; 

__attribute__((used)) static float compare(const AVFrame *haystack, const AVFrame *obj, int offx, int offy)
{
    int x,y;
    int o_sum_v = 0;
    int h_sum_v = 0;
    int64_t oo_sum_v = 0;
    int64_t hh_sum_v = 0;
    int64_t oh_sum_v = 0;
    float c;
    int n = obj->height * obj->width;
    const uint8_t *odat = obj     ->data[0];
    const uint8_t *hdat = haystack->data[0] + offx + offy * haystack->linesize[0];
    int64_t o_sigma, h_sigma;

    for(y = 0; y < obj->height; y++) {
        for(x = 0; x < obj->width; x++) {
            int o_v = odat[x];
            int h_v = hdat[x];
            o_sum_v += o_v;
            h_sum_v += h_v;
            oo_sum_v += o_v * o_v;
            hh_sum_v += h_v * h_v;
            oh_sum_v += o_v * h_v;
        }
        odat += obj->linesize[0];
        hdat += haystack->linesize[0];
    }
    o_sigma = n*oo_sum_v - o_sum_v*(int64_t)o_sum_v;
    h_sigma = n*hh_sum_v - h_sum_v*(int64_t)h_sum_v;

    if (o_sigma == 0 || h_sigma == 0)
        return 1.0;

    c = (n*oh_sum_v - o_sum_v*(int64_t)h_sum_v) / (sqrt(o_sigma)*sqrt(h_sigma));

    return 1 - fabs(c);
}