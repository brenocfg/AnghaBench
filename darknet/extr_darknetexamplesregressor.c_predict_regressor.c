#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ network ;
struct TYPE_11__ {float* data; } ;
typedef  TYPE_2__ image ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 TYPE_2__ letterbox_image (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float* network_predict (TYPE_1__*,float*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 double sec (scalar_t__) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 

void predict_regressor(char *cfgfile, char *weightfile, char *filename)
{
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
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
        image sized = letterbox_image(im, net->w, net->h);

        float *X = sized.data;
        time=clock();
        float *predictions = network_predict(net, X);
        printf("Predicted: %f\n", predictions[0]);
        printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        free_image(im);
        free_image(sized);
        if (filename) break;
    }
}