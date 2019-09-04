#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int n; int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ network ;
struct TYPE_14__ {int w; int h; int c; float* data; } ;
typedef  TYPE_2__ image ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ clock () ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 TYPE_2__ get_network_image_layer (TYPE_1__*,int) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ make_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_predict (TYPE_1__*,float*) ; 
 int /*<<< orphan*/  normalize_image (TYPE_2__) ; 
 int /*<<< orphan*/  printf (char*,char*,double) ; 
 float rand_normal () ; 
 int /*<<< orphan*/  save_image (TYPE_2__,char*) ; 
 double sec (scalar_t__) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  show_image (TYPE_2__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (int) ; 

void test_dcgan(char *cfgfile, char *weightfile)
{
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);

    clock_t time;
    char buff[256];
    char *input = buff;
    int imlayer = 0;

    imlayer = net->n-1;

    while(1){
        image im = make_image(net->w, net->h, net->c);
        int i;
        for(i = 0; i < im.w*im.h*im.c; ++i){
            im.data[i] = rand_normal();
        }
        //float mag = mag_array(im.data, im.w*im.h*im.c);
        //scale_array(im.data, im.w*im.h*im.c, 1./mag);

        float *X = im.data;
        time=clock();
        network_predict(net, X);
        image out = get_network_image_layer(net, imlayer);
        //yuv_to_rgb(out);
        normalize_image(out);
        printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        save_image(out, "out");
        show_image(out, "out", 0);

        free_image(im);
    }
}