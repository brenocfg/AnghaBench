#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ sortable_bbox ;
struct TYPE_13__ {int w; int h; int c; } ;
typedef  TYPE_2__ network ;
struct TYPE_14__ {int w; int h; int c; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 int /*<<< orphan*/  bbox_update (TYPE_1__*,TYPE_1__*,int,int) ; 
 float* calloc (int,int) ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 TYPE_3__ load_image_color (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int) ; 
 float* network_predict (TYPE_2__,float*) ; 
 int /*<<< orphan*/  total_compares ; 

void bbox_fight(network net, sortable_bbox *a, sortable_bbox *b, int classes, int class)
{
    image im1 = load_image_color(a->filename, net.w, net.h);
    image im2 = load_image_color(b->filename, net.w, net.h);
    float *X  = calloc(net.w*net.h*net.c, sizeof(float));
    memcpy(X,                   im1.data, im1.w*im1.h*im1.c*sizeof(float));
    memcpy(X+im1.w*im1.h*im1.c, im2.data, im2.w*im2.h*im2.c*sizeof(float));
    float *predictions = network_predict(net, X);
    ++total_compares;

    int i;
    for(i = 0; i < classes; ++i){
        if(class < 0 || class == i){
            int result = predictions[i*2] > predictions[i*2+1];
            bbox_update(a, b, i, result);
        }
    }
    
    free_image(im1);
    free_image(im2);
    free(X);
}