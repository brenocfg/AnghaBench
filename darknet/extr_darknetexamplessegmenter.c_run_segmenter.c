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
 int /*<<< orphan*/  demo_segmenter (char*,char*,char*,int,char*) ; 
 int find_arg (int,char**,char*) ; 
 char* find_char_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 int find_int_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int gpu_index ; 
 int /*<<< orphan*/  predict_segmenter (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  train_segmenter (char*,char*,char*,int*,int,int,int) ; 

void run_segmenter(int argc, char **argv)
{
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

    int cam_index = find_int_arg(argc, argv, "-c", 0);
    int clear = find_arg(argc, argv, "-clear");
    int display = find_arg(argc, argv, "-display");
    char *data = argv[3];
    char *cfg = argv[4];
    char *weights = (argc > 5) ? argv[5] : 0;
    char *filename = (argc > 6) ? argv[6]: 0;
    if(0==strcmp(argv[2], "test")) predict_segmenter(data, cfg, weights, filename);
    else if(0==strcmp(argv[2], "train")) train_segmenter(data, cfg, weights, gpus, ngpus, clear, display);
    else if(0==strcmp(argv[2], "demo")) demo_segmenter(data, cfg, weights, cam_index, filename);
}