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
 int /*<<< orphan*/  atof (char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  average (int,char**) ; 
 int /*<<< orphan*/  composite_3d (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  denormalize_net (char*,char*,char*) ; 
 int find_arg (int,char**,char*) ; 
 char* find_char_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 float find_float_arg (int,char**,char*,double) ; 
 int find_int_arg (int,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int gpu_index ; 
 int /*<<< orphan*/  mkimg (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  normalize_net (char*,char*,char*) ; 
 int /*<<< orphan*/  oneoff (char*,char*,char*) ; 
 int /*<<< orphan*/  oneoff2 (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  operations (char*) ; 
 int /*<<< orphan*/  partial (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  predict_classifier (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  print_weights (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rescale_net (char*,char*,char*) ; 
 int /*<<< orphan*/  reset_normalize_net (char*,char*,char*) ; 
 int /*<<< orphan*/  rgbgr_net (char*,char*,char*) ; 
 int /*<<< orphan*/  run_art (int,char**) ; 
 int /*<<< orphan*/  run_char_rnn (int,char**) ; 
 int /*<<< orphan*/  run_cifar (int,char**) ; 
 int /*<<< orphan*/  run_classifier (int,char**) ; 
 int /*<<< orphan*/  run_coco (int,char**) ; 
 int /*<<< orphan*/  run_detector (int,char**) ; 
 int /*<<< orphan*/  run_go (int,char**) ; 
 int /*<<< orphan*/  run_isegmenter (int,char**) ; 
 int /*<<< orphan*/  run_lsd (int,char**) ; 
 int /*<<< orphan*/  run_nightmare (int,char**) ; 
 int /*<<< orphan*/  run_regressor (int,char**) ; 
 int /*<<< orphan*/  run_segmenter (int,char**) ; 
 int /*<<< orphan*/  run_super (int,char**) ; 
 int /*<<< orphan*/  run_tag (int,char**) ; 
 int /*<<< orphan*/  run_yolo (int,char**) ; 
 int /*<<< orphan*/  speed (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statistics_net (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_detector (char*,char*,char*,char*,float,double,char*,int) ; 
 int /*<<< orphan*/  test_resize (char*) ; 
 int /*<<< orphan*/  visualize (char*,char*) ; 

int main(int argc, char **argv)
{
    //test_resize("data/bad.jpg");
    //test_box();
    //test_convolutional_layer();
    if(argc < 2){
        fprintf(stderr, "usage: %s <function>\n", argv[0]);
        return 0;
    }
    gpu_index = find_int_arg(argc, argv, "-i", 0);
    if(find_arg(argc, argv, "-nogpu")) {
        gpu_index = -1;
    }

#ifndef GPU
    gpu_index = -1;
#else
    if(gpu_index >= 0){
        cuda_set_device(gpu_index);
    }
#endif

    if (0 == strcmp(argv[1], "average")){
        average(argc, argv);
    } else if (0 == strcmp(argv[1], "yolo")){
        run_yolo(argc, argv);
    } else if (0 == strcmp(argv[1], "super")){
        run_super(argc, argv);
    } else if (0 == strcmp(argv[1], "lsd")){
        run_lsd(argc, argv);
    } else if (0 == strcmp(argv[1], "detector")){
        run_detector(argc, argv);
    } else if (0 == strcmp(argv[1], "detect")){
        float thresh = find_float_arg(argc, argv, "-thresh", .5);
        char *filename = (argc > 4) ? argv[4]: 0;
        char *outfile = find_char_arg(argc, argv, "-out", 0);
        int fullscreen = find_arg(argc, argv, "-fullscreen");
        test_detector("cfg/coco.data", argv[2], argv[3], filename, thresh, .5, outfile, fullscreen);
    } else if (0 == strcmp(argv[1], "cifar")){
        run_cifar(argc, argv);
    } else if (0 == strcmp(argv[1], "go")){
        run_go(argc, argv);
    } else if (0 == strcmp(argv[1], "rnn")){
        run_char_rnn(argc, argv);
    } else if (0 == strcmp(argv[1], "coco")){
        run_coco(argc, argv);
    } else if (0 == strcmp(argv[1], "classify")){
        predict_classifier("cfg/imagenet1k.data", argv[2], argv[3], argv[4], 5);
    } else if (0 == strcmp(argv[1], "classifier")){
        run_classifier(argc, argv);
    } else if (0 == strcmp(argv[1], "regressor")){
        run_regressor(argc, argv);
    } else if (0 == strcmp(argv[1], "isegmenter")){
        run_isegmenter(argc, argv);
    } else if (0 == strcmp(argv[1], "segmenter")){
        run_segmenter(argc, argv);
    } else if (0 == strcmp(argv[1], "art")){
        run_art(argc, argv);
    } else if (0 == strcmp(argv[1], "tag")){
        run_tag(argc, argv);
    } else if (0 == strcmp(argv[1], "3d")){
        composite_3d(argv[2], argv[3], argv[4], (argc > 5) ? atof(argv[5]) : 0);
    } else if (0 == strcmp(argv[1], "test")){
        test_resize(argv[2]);
    } else if (0 == strcmp(argv[1], "nightmare")){
        run_nightmare(argc, argv);
    } else if (0 == strcmp(argv[1], "rgbgr")){
        rgbgr_net(argv[2], argv[3], argv[4]);
    } else if (0 == strcmp(argv[1], "reset")){
        reset_normalize_net(argv[2], argv[3], argv[4]);
    } else if (0 == strcmp(argv[1], "denormalize")){
        denormalize_net(argv[2], argv[3], argv[4]);
    } else if (0 == strcmp(argv[1], "statistics")){
        statistics_net(argv[2], argv[3]);
    } else if (0 == strcmp(argv[1], "normalize")){
        normalize_net(argv[2], argv[3], argv[4]);
    } else if (0 == strcmp(argv[1], "rescale")){
        rescale_net(argv[2], argv[3], argv[4]);
    } else if (0 == strcmp(argv[1], "ops")){
        operations(argv[2]);
    } else if (0 == strcmp(argv[1], "speed")){
        speed(argv[2], (argc > 3 && argv[3]) ? atoi(argv[3]) : 0);
    } else if (0 == strcmp(argv[1], "oneoff")){
        oneoff(argv[2], argv[3], argv[4]);
    } else if (0 == strcmp(argv[1], "oneoff2")){
        oneoff2(argv[2], argv[3], argv[4], atoi(argv[5]));
    } else if (0 == strcmp(argv[1], "print")){
        print_weights(argv[2], argv[3], atoi(argv[4]));
    } else if (0 == strcmp(argv[1], "partial")){
        partial(argv[2], argv[3], argv[4], atoi(argv[5]));
    } else if (0 == strcmp(argv[1], "average")){
        average(argc, argv);
    } else if (0 == strcmp(argv[1], "visualize")){
        visualize(argv[2], (argc > 3) ? argv[3] : 0);
    } else if (0 == strcmp(argv[1], "mkimg")){
        mkimg(argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), argv[7]);
    } else if (0 == strcmp(argv[1], "imtest")){
        test_resize(argv[2]);
    } else {
        fprintf(stderr, "Not an option: %s\n", argv[1]);
    }
    return 0;
}