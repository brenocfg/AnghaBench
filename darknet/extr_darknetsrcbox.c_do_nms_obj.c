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
struct TYPE_4__ {scalar_t__ objectness; int sort_class; scalar_t__* prob; int /*<<< orphan*/  bbox; } ;
typedef  TYPE_1__ detection ;
typedef  int /*<<< orphan*/  box ;

/* Variables and functions */
 float box_iou (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nms_comparator ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

void do_nms_obj(detection *dets, int total, int classes, float thresh)
{
    int i, j, k;
    k = total-1;
    for(i = 0; i <= k; ++i){
        if(dets[i].objectness == 0){
            detection swap = dets[i];
            dets[i] = dets[k];
            dets[k] = swap;
            --k;
            --i;
        }
    }
    total = k+1;

    for(i = 0; i < total; ++i){
        dets[i].sort_class = -1;
    }

    qsort(dets, total, sizeof(detection), nms_comparator);
    for(i = 0; i < total; ++i){
        if(dets[i].objectness == 0) continue;
        box a = dets[i].bbox;
        for(j = i+1; j < total; ++j){
            if(dets[j].objectness == 0) continue;
            box b = dets[j].bbox;
            if (box_iou(a, b) > thresh){
                dets[j].objectness = 0;
                for(k = 0; k < classes; ++k){
                    dets[j].prob[k] = 0;
                }
            }
        }
    }
}