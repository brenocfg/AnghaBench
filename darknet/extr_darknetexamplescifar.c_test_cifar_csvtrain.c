#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
typedef  int /*<<< orphan*/  matrix ;
typedef  int /*<<< orphan*/  image ;
struct TYPE_6__ {int rows; int /*<<< orphan*/ * vals; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; TYPE_1__ X; } ;
typedef  TYPE_2__ data ;

/* Variables and functions */
 int /*<<< orphan*/  flip_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_to_image (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double) ; 
 int /*<<< orphan*/  free_data (TYPE_2__) ; 
 TYPE_2__ load_all_cifar10 () ; 
 int /*<<< orphan*/ * load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_add_matrix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_to_csv (int /*<<< orphan*/ ) ; 
 double matrix_topk_accuracy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  network_predict_data (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  scale_matrix (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void test_cifar_csvtrain(char *cfg, char *weights)
{
    network *net = load_network(cfg, weights, 0);
    srand(time(0));

    data test = load_all_cifar10();

    matrix pred = network_predict_data(net, test);

    int i;
    for(i = 0; i < test.X.rows; ++i){
        image im = float_to_image(32, 32, 3, test.X.vals[i]);
        flip_image(im);
    }
    matrix pred2 = network_predict_data(net, test);
    scale_matrix(pred, .5);
    scale_matrix(pred2, .5);
    matrix_add_matrix(pred2, pred);

    matrix_to_csv(pred);
    fprintf(stderr, "Accuracy: %f\n", matrix_topk_accuracy(test.y, pred, 1));
    free_data(test);
}