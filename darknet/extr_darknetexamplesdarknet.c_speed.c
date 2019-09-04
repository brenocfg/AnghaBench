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
struct TYPE_8__ {int c; int batch; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ network ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ image ;

/* Variables and functions */
 TYPE_2__ make_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  network_predict (TYPE_1__*,int /*<<< orphan*/ ) ; 
 long numops (TYPE_1__*) ; 
 TYPE_1__* parse_network_cfg (char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 double what_time_is_it_now () ; 

void speed(char *cfgfile, int tics)
{
    if (tics == 0) tics = 1000;
    network *net = parse_network_cfg(cfgfile);
    set_batch_network(net, 1);
    int i;
    double time=what_time_is_it_now();
    image im = make_image(net->w, net->h, net->c*net->batch);
    for(i = 0; i < tics; ++i){
        network_predict(net, im.data);
    }
    double t = what_time_is_it_now() - time;
    long ops = numops(net);
    printf("\n%d evals, %f Seconds\n", tics, t);
    printf("Floating Point Operations: %.2f Bn\n", (float)ops/1000000000.);
    printf("FLOPS: %.2f Bn\n", (float)ops/1000000000.*tics/t);
    printf("Speed: %f sec/eval\n", t/tics);
    printf("Speed: %f Hz\n", tics/t);
}