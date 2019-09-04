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
 int /*<<< orphan*/  csv_classifier (char*,char*,char*) ; 
 int /*<<< orphan*/  demo_classifier (char*,char*,char*,int,char*) ; 
 int /*<<< orphan*/  file_output_classifier (char*,char*,char*,char*) ; 
 int find_arg (int,char**,char*) ; 
 char* find_char_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 int find_int_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  gpu_index ; 
 int /*<<< orphan*/  gun_classifier (char*,char*,char*,int,char*) ; 
 int /*<<< orphan*/  label_classifier (char*,char*,char*) ; 
 int /*<<< orphan*/  predict_classifier (char*,char*,char*,char*,int) ; 
 int* read_intlist (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_classifier (char*,char*,char*,int) ; 
 int /*<<< orphan*/  threat_classifier (char*,char*,char*,int,char*) ; 
 int /*<<< orphan*/  train_classifier (char*,char*,char*,int*,int,int) ; 
 int /*<<< orphan*/  try_classifier (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  validate_classifier_10 (char*,char*,char*) ; 
 int /*<<< orphan*/  validate_classifier_crop (char*,char*,char*) ; 
 int /*<<< orphan*/  validate_classifier_full (char*,char*,char*) ; 
 int /*<<< orphan*/  validate_classifier_multi (char*,char*,char*) ; 
 int /*<<< orphan*/  validate_classifier_single (char*,char*,char*) ; 

void run_classifier(int argc, char **argv)
{
    if(argc < 4){
        fprintf(stderr, "usage: %s %s [train/test/valid] [cfg] [weights (optional)]\n", argv[0], argv[1]);
        return;
    }

    char *gpu_list = find_char_arg(argc, argv, "-gpus", 0);
    int ngpus;
    int *gpus = read_intlist(gpu_list, &ngpus, gpu_index);


    int cam_index = find_int_arg(argc, argv, "-c", 0);
    int top = find_int_arg(argc, argv, "-t", 0);
    int clear = find_arg(argc, argv, "-clear");
    char *data = argv[3];
    char *cfg = argv[4];
    char *weights = (argc > 5) ? argv[5] : 0;
    char *filename = (argc > 6) ? argv[6]: 0;
    char *layer_s = (argc > 7) ? argv[7]: 0;
    int layer = layer_s ? atoi(layer_s) : -1;
    if(0==strcmp(argv[2], "predict")) predict_classifier(data, cfg, weights, filename, top);
    else if(0==strcmp(argv[2], "fout")) file_output_classifier(data, cfg, weights, filename);
    else if(0==strcmp(argv[2], "try")) try_classifier(data, cfg, weights, filename, atoi(layer_s));
    else if(0==strcmp(argv[2], "train")) train_classifier(data, cfg, weights, gpus, ngpus, clear);
    else if(0==strcmp(argv[2], "demo")) demo_classifier(data, cfg, weights, cam_index, filename);
    else if(0==strcmp(argv[2], "gun")) gun_classifier(data, cfg, weights, cam_index, filename);
    else if(0==strcmp(argv[2], "threat")) threat_classifier(data, cfg, weights, cam_index, filename);
    else if(0==strcmp(argv[2], "test")) test_classifier(data, cfg, weights, layer);
    else if(0==strcmp(argv[2], "csv")) csv_classifier(data, cfg, weights);
    else if(0==strcmp(argv[2], "label")) label_classifier(data, cfg, weights);
    else if(0==strcmp(argv[2], "valid")) validate_classifier_single(data, cfg, weights);
    else if(0==strcmp(argv[2], "validmulti")) validate_classifier_multi(data, cfg, weights);
    else if(0==strcmp(argv[2], "valid10")) validate_classifier_10(data, cfg, weights);
    else if(0==strcmp(argv[2], "validcrop")) validate_classifier_crop(data, cfg, weights);
    else if(0==strcmp(argv[2], "validfull")) validate_classifier_full(data, cfg, weights);
}