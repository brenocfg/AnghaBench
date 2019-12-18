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
struct TYPE_18__ {int n; int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* layers; } ;
typedef  TYPE_2__ network ;
struct TYPE_19__ {float* data; int w; int h; int c; } ;
typedef  TYPE_3__ image ;
typedef  scalar_t__ clock_t ;
struct TYPE_17__ {int out_c; } ;

/* Variables and functions */
 scalar_t__ clock () ; 
 TYPE_3__ copy_image (TYPE_3__) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 TYPE_3__ get_network_image_layer (TYPE_2__*,int) ; 
 TYPE_2__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ make_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_predict (TYPE_2__*,float*) ; 
 int /*<<< orphan*/  normalize_image (TYPE_3__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_3__ random_unit_vector_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_image (TYPE_3__,char*) ; 
 double sec (scalar_t__) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_2__*,int) ; 
 int /*<<< orphan*/  show_image (TYPE_3__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slerp (float*,float*,float,int,float*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  srand (int) ; 

void inter_dcgan(char *cfgfile, char *weightfile)
{
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);

    clock_t time;
    char buff[256];
    char *input = buff;
    int i, imlayer = 0;

    for (i = 0; i < net->n; ++i) {
        if (net->layers[i].out_c == 3) {
            imlayer = i;
            printf("%d\n", i);
            break;
        }
    }
    image start = random_unit_vector_image(net->w, net->h, net->c);
    image end = random_unit_vector_image(net->w, net->h, net->c);
        image im = make_image(net->w, net->h, net->c);
        image orig = copy_image(start);

    int c = 0;
    int count = 0;
    int max_count = 15;
    while(1){
        ++c;
        
        if(count == max_count){
            count = 0;
            free_image(start);
            start = end;
            end = random_unit_vector_image(net->w, net->h, net->c);
            if(c > 300){
                end = orig;
            }
            if(c>300 + max_count) return;
        }
        ++count;

        slerp(start.data, end.data, (float)count / max_count, im.w*im.h*im.c, im.data);

        float *X = im.data;
        time=clock();
        network_predict(net, X);
        image out = get_network_image_layer(net, imlayer);
        //yuv_to_rgb(out);
        normalize_image(out);
        printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        //char buff[256];
        sprintf(buff, "out%05d", c);
        save_image(out, "out");
        save_image(out, buff);
        show_image(out, "out", 0);
    }
}