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

void threat_classifier(char *datacfg, char *cfgfile, char *weightfile, int cam_index, const char *filename)
{
#ifdef OPENCV
    float threat = 0;
    float roll = .2;

    printf("Classifier Demo\n");
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    list *options = read_data_cfg(datacfg);

    srand(2222222);
    void * cap = open_video_stream(filename, cam_index, 0,0,0);

    int top = option_find_int(options, "top", 1);

    char *name_list = option_find_str(options, "names", 0);
    char **names = get_labels(name_list);

    int *indexes = calloc(top, sizeof(int));

    if(!cap) error("Couldn't connect to webcam.\n");
    //cvNamedWindow("Threat", CV_WINDOW_NORMAL); 
    //cvResizeWindow("Threat", 512, 512);
    float fps = 0;
    int i;

    int count = 0;

    while(1){
        ++count;
        struct timeval tval_before, tval_after, tval_result;
        gettimeofday(&tval_before, NULL);

        image in = get_image_from_stream(cap);
        if(!in.data) break;
        image in_s = resize_image(in, net->w, net->h);

        image out = in;
        int x1 = out.w / 20;
        int y1 = out.h / 20;
        int x2 = 2*x1;
        int y2 = out.h - out.h/20;

        int border = .01*out.h;
        int h = y2 - y1 - 2*border;
        int w = x2 - x1 - 2*border;

        float *predictions = network_predict(net, in_s.data);
        float curr_threat = 0;
        if(1){
            curr_threat = predictions[0] * 0 + 
                predictions[1] * .6 + 
                predictions[2];
        } else {
            curr_threat = predictions[218] +
                predictions[539] + 
                predictions[540] + 
                predictions[368] + 
                predictions[369] + 
                predictions[370];
        }
        threat = roll * curr_threat + (1-roll) * threat;

        draw_box_width(out, x2 + border, y1 + .02*h, x2 + .5 * w, y1 + .02*h + border, border, 0,0,0);
        if(threat > .97) {
            draw_box_width(out,  x2 + .5 * w + border,
                    y1 + .02*h - 2*border, 
                    x2 + .5 * w + 6*border, 
                    y1 + .02*h + 3*border, 3*border, 1,0,0);
        }
        draw_box_width(out,  x2 + .5 * w + border,
                y1 + .02*h - 2*border, 
                x2 + .5 * w + 6*border, 
                y1 + .02*h + 3*border, .5*border, 0,0,0);
        draw_box_width(out, x2 + border, y1 + .42*h, x2 + .5 * w, y1 + .42*h + border, border, 0,0,0);
        if(threat > .57) {
            draw_box_width(out,  x2 + .5 * w + border,
                    y1 + .42*h - 2*border, 
                    x2 + .5 * w + 6*border, 
                    y1 + .42*h + 3*border, 3*border, 1,1,0);
        }
        draw_box_width(out,  x2 + .5 * w + border,
                y1 + .42*h - 2*border, 
                x2 + .5 * w + 6*border, 
                y1 + .42*h + 3*border, .5*border, 0,0,0);

        draw_box_width(out, x1, y1, x2, y2, border, 0,0,0);
        for(i = 0; i < threat * h ; ++i){
            float ratio = (float) i / h;
            float r = (ratio < .5) ? (2*(ratio)) : 1;
            float g = (ratio < .5) ? 1 : 1 - 2*(ratio - .5);
            draw_box_width(out, x1 + border, y2 - border - i, x2 - border, y2 - border - i, 1, r, g, 0);
        }
        top_predictions(net, top, indexes);
        char buff[256];
        sprintf(buff, "/home/pjreddie/tmp/threat_%06d", count);
        //save_image(out, buff);

        printf("\033[2J");
        printf("\033[1;1H");
        printf("\nFPS:%.0f\n",fps);

        for(i = 0; i < top; ++i){
            int index = indexes[i];
            printf("%.1f%%: %s\n", predictions[index]*100, names[index]);
        }

        if(1){
            show_image(out, "Threat", 10);
        }
        free_image(in_s);
        free_image(in);

        gettimeofday(&tval_after, NULL);
        timersub(&tval_after, &tval_before, &tval_result);
        float curr = 1000000.f/((long int)tval_result.tv_usec);
        fps = .9*fps + .1*curr;
    }
#endif
}