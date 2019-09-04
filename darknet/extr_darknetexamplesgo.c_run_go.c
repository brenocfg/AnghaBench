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
 int atoi (char*) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  engine_go (char*,char*,int,float,float,float,int,int) ; 
 int find_arg (int,char**,char*) ; 
 char* find_char_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 float find_float_arg (int,char**,char*,double) ; 
 int find_int_arg (int,char**,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int gpu_index ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  self_go (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_go (char*,char*,int) ; 
 int /*<<< orphan*/  train_go (char*,char*,char*,int*,int,int) ; 
 int /*<<< orphan*/  valid_go (char*,char*,int,char*) ; 

void run_go(int argc, char **argv)
{
    //boards_go();
    if(argc < 4){
        fprintf(stderr, "usage: %s %s [train/test/valid] [cfg] [weights (optional)]\n", argv[0], argv[1]);
        return;
    }

    char *gpu_list = find_char_arg(argc, argv, "-gpus", 0);
    int *gpus = 0;
    int gpu = 0;
    int ngpus = 0;
    if(gpu_list){
        printf("%s\n", gpu_list);
        int len = strlen(gpu_list);
        ngpus = 1;
        int i;
        for(i = 0; i < len; ++i){
            if (gpu_list[i] == ',') ++ngpus;
        }
        gpus = calloc(ngpus, sizeof(int));
        for(i = 0; i < ngpus; ++i){
            gpus[i] = atoi(gpu_list);
            gpu_list = strchr(gpu_list, ',')+1;
        }
    } else {
        gpu = gpu_index;
        gpus = &gpu;
        ngpus = 1;
    }
    int clear = find_arg(argc, argv, "-clear");

    char *cfg = argv[3];
    char *weights = (argc > 4) ? argv[4] : 0;
    char *c2 = (argc > 5) ? argv[5] : 0;
    char *w2 = (argc > 6) ? argv[6] : 0;
    int multi = find_arg(argc, argv, "-multi");
    int anon = find_arg(argc, argv, "-anon");
    int iters = find_int_arg(argc, argv, "-iters", 500);
    int resign = find_int_arg(argc, argv, "-resign", 175);
    float cpuct = find_float_arg(argc, argv, "-cpuct", 5);
    float temp = find_float_arg(argc, argv, "-temp", .1);
    float time = find_float_arg(argc, argv, "-time", 0);
    if(0==strcmp(argv[2], "train")) train_go(cfg, weights, c2, gpus, ngpus, clear);
    else if(0==strcmp(argv[2], "valid")) valid_go(cfg, weights, multi, c2);
    else if(0==strcmp(argv[2], "self")) self_go(cfg, weights, c2, w2, multi);
    else if(0==strcmp(argv[2], "test")) test_go(cfg, weights, multi);
    else if(0==strcmp(argv[2], "engine")) engine_go(cfg, weights, iters, time, temp, cpuct, anon, resign);
}