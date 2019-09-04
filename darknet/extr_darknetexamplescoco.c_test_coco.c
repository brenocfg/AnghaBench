#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int n; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_18__ {int side; int n; int /*<<< orphan*/  classes; } ;
typedef  TYPE_2__ layer ;
struct TYPE_19__ {float* data; } ;
typedef  TYPE_3__ image ;
typedef  int /*<<< orphan*/  detection ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ clock () ; 
 int /*<<< orphan*/  coco_classes ; 
 int /*<<< orphan*/  do_nms_sort (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  draw_detections (TYPE_3__,int /*<<< orphan*/ *,int,float,int /*<<< orphan*/ ,TYPE_3__**,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_detections (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 int /*<<< orphan*/ * get_network_boxes (TYPE_1__*,int,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__** load_alphabet () ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_predict (TYPE_1__*,float*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_3__ resize_image (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_image (TYPE_3__,char*) ; 
 double sec (scalar_t__) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  show_image (TYPE_3__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 

void test_coco(char *cfgfile, char *weightfile, char *filename, float thresh)
{
    image **alphabet = load_alphabet();
    network *net = load_network(cfgfile, weightfile, 0);
    layer l = net->layers[net->n-1];
    set_batch_network(net, 1);
    srand(2222222);
    float nms = .4;
    clock_t time;
    char buff[256];
    char *input = buff;
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        } else {
            printf("Enter Image Path: ");
            fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return;
            strtok(input, "\n");
        }
        image im = load_image_color(input,0,0);
        image sized = resize_image(im, net->w, net->h);
        float *X = sized.data;
        time=clock();
        network_predict(net, X);
        printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));

        int nboxes = 0;
        detection *dets = get_network_boxes(net, 1, 1, thresh, 0, 0, 0, &nboxes);
        if (nms) do_nms_sort(dets, l.side*l.side*l.n, l.classes, nms);

        draw_detections(im, dets, l.side*l.side*l.n, thresh, coco_classes, alphabet, 80);
        save_image(im, "prediction");
        show_image(im, "predictions", 0);
        free_detections(dets, nboxes);
        free_image(im);
        free_image(sized);
        if (filename) break;
    }
}