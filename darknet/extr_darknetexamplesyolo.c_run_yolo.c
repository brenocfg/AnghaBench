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
 int /*<<< orphan*/  demo (char*,char*,float,int,char*,int /*<<< orphan*/ ,int,int,char*,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* find_char_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 float find_float_arg (int,char**,char*,double) ; 
 int find_int_arg (int,char**,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_yolo (char*,char*,char*,float) ; 
 int /*<<< orphan*/  train_yolo (char*,char*) ; 
 int /*<<< orphan*/  validate_yolo (char*,char*) ; 
 int /*<<< orphan*/  validate_yolo_recall (char*,char*) ; 
 int /*<<< orphan*/  voc_names ; 

void run_yolo(int argc, char **argv)
{
    char *prefix = find_char_arg(argc, argv, "-prefix", 0);
    float thresh = find_float_arg(argc, argv, "-thresh", .2);
    int cam_index = find_int_arg(argc, argv, "-c", 0);
    int frame_skip = find_int_arg(argc, argv, "-s", 0);
    if(argc < 4){
        fprintf(stderr, "usage: %s %s [train/test/valid] [cfg] [weights (optional)]\n", argv[0], argv[1]);
        return;
    }

    int avg = find_int_arg(argc, argv, "-avg", 1);
    char *cfg = argv[3];
    char *weights = (argc > 4) ? argv[4] : 0;
    char *filename = (argc > 5) ? argv[5]: 0;
    if(0==strcmp(argv[2], "test")) test_yolo(cfg, weights, filename, thresh);
    else if(0==strcmp(argv[2], "train")) train_yolo(cfg, weights);
    else if(0==strcmp(argv[2], "valid")) validate_yolo(cfg, weights);
    else if(0==strcmp(argv[2], "recall")) validate_yolo_recall(cfg, weights);
    else if(0==strcmp(argv[2], "demo")) demo(cfg, weights, thresh, cam_index, filename, voc_names, 20, frame_skip, prefix, avg, .5, 0,0,0,0);
}