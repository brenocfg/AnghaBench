#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
struct TYPE_10__ {int w; int h; int c; float* data; } ;
typedef  TYPE_1__ image ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ clock () ; 
 int /*<<< orphan*/  cvDestroyAllWindows () ; 
 int /*<<< orphan*/  cvWaitKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_image (TYPE_1__) ; 
 TYPE_1__ get_network_image (int /*<<< orphan*/ ) ; 
 TYPE_1__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_weights (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  network_predict (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  parse_network_cfg (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ resize_image (TYPE_1__,int,int) ; 
 int /*<<< orphan*/  resize_network (int /*<<< orphan*/ *,int,int) ; 
 double sec (scalar_t__) ; 
 int /*<<< orphan*/  set_batch_network (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  show_image (TYPE_1__,char*) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 
 TYPE_1__ threshold_image (TYPE_1__,double) ; 

void test_writing(char *cfgfile, char *weightfile, char *filename)
{
    network net = parse_network_cfg(cfgfile);
    if(weightfile){
        load_weights(&net, weightfile);
    }
    set_batch_network(&net, 1);
    srand(2222222);
    clock_t time;
    char buff[256];
    char *input = buff;
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        }else{
            printf("Enter Image Path: ");
            fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return;
            strtok(input, "\n");
        }

        image im = load_image_color(input, 0, 0);
        resize_network(&net, im.w, im.h);
        printf("%d %d %d\n", im.h, im.w, im.c);
        float *X = im.data;
        time=clock();
        network_predict(net, X);
        printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        image pred = get_network_image(net);

        image upsampled = resize_image(pred, im.w, im.h);
        image thresh = threshold_image(upsampled, .5);
        pred = thresh;

        show_image(pred, "prediction");
        show_image(im, "orig");
#ifdef OPENCV
        cvWaitKey(0);
        cvDestroyAllWindows();
#endif

        free_image(upsampled);
        free_image(thresh);
        free_image(im);
        if (filename) break;
    }
}