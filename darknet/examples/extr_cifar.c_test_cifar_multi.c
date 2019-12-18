#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ image ;
struct TYPE_10__ {float** vals; } ;
struct TYPE_9__ {int rows; int /*<<< orphan*/ * vals; } ;
struct TYPE_12__ {TYPE_2__ y; TYPE_1__ X; } ;
typedef  TYPE_4__ data ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int,int,float*,int,float*,int) ; 
 int /*<<< orphan*/  flip_image (TYPE_3__) ; 
 TYPE_3__ float_to_image (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 TYPE_4__ load_cifar10_data (char*) ; 
 int /*<<< orphan*/ * load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int max_index (float*,int) ; 
 float* network_predict (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  set_batch_network (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void test_cifar_multi(char *filename, char *weightfile)
{
    network *net = load_network(filename, weightfile, 0);
    set_batch_network(net, 1);
    srand(time(0));

    float avg_acc = 0;
    data test = load_cifar10_data("data/cifar/cifar-10-batches-bin/test_batch.bin");

    int i;
    for(i = 0; i < test.X.rows; ++i){
        image im = float_to_image(32, 32, 3, test.X.vals[i]);

        float pred[10] = {0};

        float *p = network_predict(net, im.data);
        axpy_cpu(10, 1, p, 1, pred, 1);
        flip_image(im);
        p = network_predict(net, im.data);
        axpy_cpu(10, 1, p, 1, pred, 1);

        int index = max_index(pred, 10);
        int class = max_index(test.y.vals[i], 10);
        if(index == class) avg_acc += 1;
        free_image(im);
        printf("%4d: %.2f%%\n", i, 100.*avg_acc/(i+1));
    }
}