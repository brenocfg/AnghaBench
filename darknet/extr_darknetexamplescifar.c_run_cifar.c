#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  eval_cifar_csv () ; 
 int /*<<< orphan*/  extract_cifar () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_cifar (char*,char*) ; 
 int /*<<< orphan*/  test_cifar_csv (char*,char*) ; 
 int /*<<< orphan*/  test_cifar_csvtrain (char*,char*) ; 
 int /*<<< orphan*/  test_cifar_multi (char*,char*) ; 
 int /*<<< orphan*/  train_cifar (char*,char*) ; 
 int /*<<< orphan*/  train_cifar_distill (char*,char*) ; 

void run_cifar(int argc, char **argv)
{
    if(argc < 4){
        fprintf(stderr, "usage: %s %s [train/test/valid] [cfg] [weights (optional)]\n", argv[0], argv[1]);
        return;
    }

    char *cfg = argv[3];
    char *weights = (argc > 4) ? argv[4] : 0;
    if(0==strcmp(argv[2], "train")) train_cifar(cfg, weights);
    else if(0==strcmp(argv[2], "extract")) extract_cifar();
    else if(0==strcmp(argv[2], "distill")) train_cifar_distill(cfg, weights);
    else if(0==strcmp(argv[2], "test")) test_cifar(cfg, weights);
    else if(0==strcmp(argv[2], "multi")) test_cifar_multi(cfg, weights);
    else if(0==strcmp(argv[2], "csv")) test_cifar_csv(cfg, weights);
    else if(0==strcmp(argv[2], "csvtrain")) test_cifar_csvtrain(cfg, weights);
    else if(0==strcmp(argv[2], "eval")) eval_cifar_csv();
}