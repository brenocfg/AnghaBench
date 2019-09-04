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

void demo_classifier(char *datacfg, char *cfgfile, char *weightfile, int cam_index, const char *filename)
{
#ifdef OPENCV
    char *base = basecfg(cfgfile);
    image **alphabet = load_alphabet();
    printf("Classifier Demo\n");
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    list *options = read_data_cfg(datacfg);

    srand(2222222);

    int w = 1280;
    int h = 720;
    void * cap = open_video_stream(filename, cam_index, w, h, 0);

    int top = option_find_int(options, "top", 1);

    char *label_list = option_find_str(options, "labels", 0);
    char *name_list = option_find_str(options, "names", label_list);
    char **names = get_labels(name_list);

    int *indexes = calloc(top, sizeof(int));

    if(!cap) error("Couldn't connect to webcam.\n");
    float fps = 0;
    int i;

    while(1){
        struct timeval tval_before, tval_after, tval_result;
        gettimeofday(&tval_before, NULL);

        image in = get_image_from_stream(cap);
        //image in_s = resize_image(in, net->w, net->h);
        image in_s = letterbox_image(in, net->w, net->h);

        float *predictions = network_predict(net, in_s.data);
        if(net->hierarchy) hierarchy_predictions(predictions, net->outputs, net->hierarchy, 1, 1);
        top_predictions(net, top, indexes);

        printf("\033[2J");
        printf("\033[1;1H");
        printf("\nFPS:%.0f\n",fps);

        int lh = in.h*.03;
        int toph = 3*lh;

        float rgb[3] = {1,1,1};
        for(i = 0; i < top; ++i){
            printf("%d\n", toph);
            int index = indexes[i];
            printf("%.1f%%: %s\n", predictions[index]*100, names[index]);

            char buff[1024];
            sprintf(buff, "%3.1f%%: %s\n", predictions[index]*100, names[index]);
            image label = get_label(alphabet, buff, lh);
            draw_label(in, toph, lh, label, rgb);
            toph += 2*lh;
            free_image(label);
        }

        show_image(in, base, 10);
        free_image(in_s);
        free_image(in);

        gettimeofday(&tval_after, NULL);
        timersub(&tval_after, &tval_before, &tval_result);
        float curr = 1000000.f/((long int)tval_result.tv_usec);
        fps = .9*fps + .1*curr;
    }
#endif
}