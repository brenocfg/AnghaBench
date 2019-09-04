#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* output; int batch; int w; int h; int n; int classes; int /*<<< orphan*/ * mask; int /*<<< orphan*/  biases; } ;
typedef  TYPE_1__ layer ;
struct TYPE_9__ {float objectness; int classes; float* prob; int /*<<< orphan*/  bbox; } ;
typedef  TYPE_2__ detection ;

/* Variables and functions */
 int /*<<< orphan*/  avg_flipped_yolo (TYPE_1__) ; 
 int /*<<< orphan*/  correct_yolo_boxes (TYPE_2__*,int,int,int,int,int,int) ; 
 int entry_index (TYPE_1__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_yolo_box (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int) ; 

int get_yolo_detections(layer l, int w, int h, int netw, int neth, float thresh, int *map, int relative, detection *dets)
{
    int i,j,n;
    float *predictions = l.output;
    if (l.batch == 2) avg_flipped_yolo(l);
    int count = 0;
    for (i = 0; i < l.w*l.h; ++i){
        int row = i / l.w;
        int col = i % l.w;
        for(n = 0; n < l.n; ++n){
            int obj_index  = entry_index(l, 0, n*l.w*l.h + i, 4);
            float objectness = predictions[obj_index];
            if(objectness <= thresh) continue;
            int box_index  = entry_index(l, 0, n*l.w*l.h + i, 0);
            dets[count].bbox = get_yolo_box(predictions, l.biases, l.mask[n], box_index, col, row, l.w, l.h, netw, neth, l.w*l.h);
            dets[count].objectness = objectness;
            dets[count].classes = l.classes;
            for(j = 0; j < l.classes; ++j){
                int class_index = entry_index(l, 0, n*l.w*l.h + i, 4 + 1 + j);
                float prob = objectness*predictions[class_index];
                dets[count].prob[j] = (prob > thresh) ? prob : 0;
            }
            ++count;
        }
    }
    correct_yolo_boxes(dets, count, w, h, netw, neth, relative);
    return count;
}