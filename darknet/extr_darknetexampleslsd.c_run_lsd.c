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
 int find_arg (int,char**,char*) ; 
 char* find_char_arg (int,char**,char*,char*) ; 
 int find_int_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  inter_dcgan (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_dcgan (char*,char*) ; 
 int /*<<< orphan*/  test_lsd (char*,char*,char*,int) ; 
 int /*<<< orphan*/  train_colorizer (char*,char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  train_dcgan (char*,char*,char*,char*,int,int,char*,int) ; 
 int /*<<< orphan*/  train_prog (char*,char*,char*,char*,int,int,char*,int) ; 

void run_lsd(int argc, char **argv)
{
    if(argc < 4){
        fprintf(stderr, "usage: %s %s [train/test/valid] [cfg] [weights (optional)]\n", argv[0], argv[1]);
        return;
    }

    int clear = find_arg(argc, argv, "-clear");
    int display = find_arg(argc, argv, "-display");
    int batches = find_int_arg(argc, argv, "-b", 0);
    char *file = find_char_arg(argc, argv, "-file", "/home/pjreddie/data/imagenet/imagenet1k.train.list");

    char *cfg = argv[3];
    char *weights = (argc > 4) ? argv[4] : 0;
    char *filename = (argc > 5) ? argv[5] : 0;
    char *acfg = argv[5];
    char *aweights = (argc > 6) ? argv[6] : 0;
    //if(0==strcmp(argv[2], "train")) train_lsd(cfg, weights, clear);
    //else if(0==strcmp(argv[2], "train2")) train_lsd2(cfg, weights, acfg, aweights, clear);
    //else if(0==strcmp(argv[2], "traincolor")) train_colorizer(cfg, weights, acfg, aweights, clear);
    //else if(0==strcmp(argv[2], "train3")) train_lsd3(argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], clear);
    if(0==strcmp(argv[2], "traingan")) train_dcgan(cfg, weights, acfg, aweights, clear, display, file, batches);
    else if(0==strcmp(argv[2], "trainprog")) train_prog(cfg, weights, acfg, aweights, clear, display, file, batches);
    else if(0==strcmp(argv[2], "traincolor")) train_colorizer(cfg, weights, acfg, aweights, clear, display);
    else if(0==strcmp(argv[2], "gan")) test_dcgan(cfg, weights);
    else if(0==strcmp(argv[2], "inter")) inter_dcgan(cfg, weights);
    else if(0==strcmp(argv[2], "test")) test_lsd(cfg, weights, filename, 0);
    else if(0==strcmp(argv[2], "color")) test_lsd(cfg, weights, filename, 1);
    /*
       else if(0==strcmp(argv[2], "valid")) validate_lsd(cfg, weights);
     */
}