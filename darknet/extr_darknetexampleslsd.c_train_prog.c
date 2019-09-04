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

void train_prog(char *cfg, char *weight, char *acfg, char *aweight, int clear, int display, char *train_images, int maxbatch)
{
#ifdef GPU
    char *backup_directory = "/home/pjreddie/backup/";
    srand(time(0));
    char *base = basecfg(cfg);
    char *abase = basecfg(acfg);
    printf("%s\n", base);
    network *gnet = load_network(cfg, weight, clear);
    network *anet = load_network(acfg, aweight, clear);

    int i, j, k;
    layer imlayer = gnet->layers[gnet->n-1];

    printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", gnet->learning_rate, gnet->momentum, gnet->decay);
    int imgs = gnet->batch*gnet->subdivisions;
    i = *gnet->seen/imgs;
    data train, buffer;


    list *plist = get_paths(train_images);
    char **paths = (char **)list_to_array(plist);

    load_args args= get_base_args(anet);
    args.paths = paths;
    args.n = imgs;
    args.m = plist->size;
    args.d = &buffer;
    args.type = CLASSIFICATION_DATA;
    args.threads=16;
    args.classes = 1;
    char *ls[2] = {"imagenet", "zzzzzzzz"};
    args.labels = ls;

    pthread_t load_thread = load_data_in_thread(args);
    clock_t time;

    gnet->train = 1;
    anet->train = 1;

    int x_size = gnet->inputs*gnet->batch;
    int y_size = gnet->truths*gnet->batch;
    float *imerror = cuda_make_array(0, y_size);

    float aloss_avg = -1;

    if (maxbatch == 0) maxbatch = gnet->max_batches;
    while (get_current_batch(gnet) < maxbatch) {
        {
            int cb = get_current_batch(gnet);
            float alpha = (float) cb / (maxbatch/2);
            if(alpha > 1) alpha = 1;
            float beta = 1 - alpha;
            printf("%f %f\n", alpha, beta);
            set_network_alpha_beta(gnet, alpha, beta);
            set_network_alpha_beta(anet, beta, alpha);
        }

        i += 1;
        time=clock();
        pthread_join(load_thread, 0);
        train = buffer;

        load_thread = load_data_in_thread(args);

        printf("Loaded: %lf seconds\n", sec(clock()-time));

        data gen = copy_data(train);
        for (j = 0; j < imgs; ++j) {
            train.y.vals[j][0] = 1;
            gen.y.vals[j][0] = 0;
        }
        time=clock();

        for (j = 0; j < gnet->subdivisions; ++j) {
            get_next_batch(train, gnet->batch, j*gnet->batch, gnet->truth, 0);
            int z;
            for(z = 0; z < x_size; ++z){
                gnet->input[z] = rand_normal();
            }
            /*
               for(z = 0; z < gnet->batch; ++z){
               float mag = mag_array(gnet->input + z*gnet->inputs, gnet->inputs);
               scale_array(gnet->input + z*gnet->inputs, gnet->inputs, 1./mag);
               }
             */
            *gnet->seen += gnet->batch;
            forward_network(gnet);

            fill_gpu(imlayer.outputs*imlayer.batch, 0, imerror, 1);
            fill_cpu(anet->truths*anet->batch, 1, anet->truth, 1);
            copy_cpu(anet->inputs*anet->batch, imlayer.output, 1, anet->input, 1);
            anet->delta_gpu = imerror;
            forward_network(anet);
            backward_network(anet);

            //float genaloss = *anet->cost / anet->batch;

            scal_gpu(imlayer.outputs*imlayer.batch, 1, imerror, 1);
            scal_gpu(imlayer.outputs*imlayer.batch, 0, gnet->layers[gnet->n-1].delta_gpu, 1);

            axpy_gpu(imlayer.outputs*imlayer.batch, 1, imerror, 1, gnet->layers[gnet->n-1].delta_gpu, 1);

            backward_network(gnet);

            for(k = 0; k < gnet->batch; ++k){
                int index = j*gnet->batch + k;
                copy_cpu(gnet->outputs, gnet->output + k*gnet->outputs, 1, gen.X.vals[index], 1);
            }
        }
        harmless_update_network_gpu(anet);

        data merge = concat_data(train, gen);
        float aloss = train_network(anet, merge);

#ifdef OPENCV
        if(display){
            image im = float_to_image(anet->w, anet->h, anet->c, gen.X.vals[0]);
            image im2 = float_to_image(anet->w, anet->h, anet->c, train.X.vals[0]);
            show_image(im, "gen", 1);
            show_image(im2, "train", 1);
            save_image(im, "gen");
            save_image(im2, "train");
        }
#endif

        update_network_gpu(gnet);

        free_data(merge);
        free_data(train);
        free_data(gen);
        if (aloss_avg < 0) aloss_avg = aloss;
        aloss_avg = aloss_avg*.9 + aloss*.1;

        printf("%d: adv: %f | adv_avg: %f, %f rate, %lf seconds, %d images\n", i, aloss, aloss_avg, get_current_rate(gnet), sec(clock()-time), i*imgs);
        if(i%10000==0){
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights", backup_directory, base, i);
            save_weights(gnet, buff);
            sprintf(buff, "%s/%s_%d.weights", backup_directory, abase, i);
            save_weights(anet, buff);
        }
        if(i%1000==0){
            char buff[256];
            sprintf(buff, "%s/%s.backup", backup_directory, base);
            save_weights(gnet, buff);
            sprintf(buff, "%s/%s.backup", backup_directory, abase);
            save_weights(anet, buff);
        }
    }
    char buff[256];
    sprintf(buff, "%s/%s_final.weights", backup_directory, base);
    save_weights(gnet, buff);
#endif
}