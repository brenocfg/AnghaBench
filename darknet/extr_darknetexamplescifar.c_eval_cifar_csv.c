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
struct TYPE_8__ {int rows; int cols; } ;
typedef  TYPE_1__ matrix ;
struct TYPE_9__ {int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ data ;

/* Variables and functions */
 TYPE_1__ csv_to_matrix (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,...) ; 
 int /*<<< orphan*/  free_data (TYPE_2__) ; 
 int /*<<< orphan*/  free_matrix (TYPE_1__) ; 
 TYPE_2__ load_cifar10_data (char*) ; 
 double matrix_topk_accuracy (int /*<<< orphan*/ ,TYPE_1__,int) ; 
 int /*<<< orphan*/  stderr ; 

void eval_cifar_csv()
{
    data test = load_cifar10_data("data/cifar/cifar-10-batches-bin/test_batch.bin");

    matrix pred = csv_to_matrix("results/combined.csv");
    fprintf(stderr, "%d %d\n", pred.rows, pred.cols);

    fprintf(stderr, "Accuracy: %f\n", matrix_topk_accuracy(test.y, pred, 1));
    free_data(test);
    free_matrix(pred);
}