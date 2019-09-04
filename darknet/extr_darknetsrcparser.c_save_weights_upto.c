#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* seen; int n; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {scalar_t__ type; int out_w; int out_h; int size; int c; int n; int* biases; int outputs; int* weights; struct TYPE_8__* output_layer; struct TYPE_8__* self_layer; struct TYPE_8__* input_layer; struct TYPE_8__* state_layer; struct TYPE_8__* update_layer; struct TYPE_8__* reset_layer; struct TYPE_8__* uh; struct TYPE_8__* ur; struct TYPE_8__* uz; struct TYPE_8__* wh; struct TYPE_8__* wr; struct TYPE_8__* wz; struct TYPE_8__* ug; struct TYPE_8__* uo; struct TYPE_8__* uf; struct TYPE_8__* ui; struct TYPE_8__* wg; struct TYPE_8__* wo; struct TYPE_8__* wf; struct TYPE_8__* wi; scalar_t__ dontsave; } ;
typedef  TYPE_2__ layer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BATCHNORM ; 
 scalar_t__ CONNECTED ; 
 scalar_t__ CONVOLUTIONAL ; 
 scalar_t__ CRNN ; 
 scalar_t__ DECONVOLUTIONAL ; 
 scalar_t__ GRU ; 
 scalar_t__ LOCAL ; 
 scalar_t__ LSTM ; 
 scalar_t__ RNN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_error (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_batchnorm_weights (TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_connected_weights (TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_convolutional_weights (TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void save_weights_upto(network *net, char *filename, int cutoff)
{
#ifdef GPU
    if(net->gpu_index >= 0){
        cuda_set_device(net->gpu_index);
    }
#endif
    fprintf(stderr, "Saving weights to %s\n", filename);
    FILE *fp = fopen(filename, "wb");
    if(!fp) file_error(filename);

    int major = 0;
    int minor = 2;
    int revision = 0;
    fwrite(&major, sizeof(int), 1, fp);
    fwrite(&minor, sizeof(int), 1, fp);
    fwrite(&revision, sizeof(int), 1, fp);
    fwrite(net->seen, sizeof(size_t), 1, fp);

    int i;
    for(i = 0; i < net->n && i < cutoff; ++i){
        layer l = net->layers[i];
        if (l.dontsave) continue;
        if(l.type == CONVOLUTIONAL || l.type == DECONVOLUTIONAL){
            save_convolutional_weights(l, fp);
        } if(l.type == CONNECTED){
            save_connected_weights(l, fp);
        } if(l.type == BATCHNORM){
            save_batchnorm_weights(l, fp);
        } if(l.type == RNN){
            save_connected_weights(*(l.input_layer), fp);
            save_connected_weights(*(l.self_layer), fp);
            save_connected_weights(*(l.output_layer), fp);
        } if (l.type == LSTM) {
            save_connected_weights(*(l.wi), fp);
            save_connected_weights(*(l.wf), fp);
            save_connected_weights(*(l.wo), fp);
            save_connected_weights(*(l.wg), fp);
            save_connected_weights(*(l.ui), fp);
            save_connected_weights(*(l.uf), fp);
            save_connected_weights(*(l.uo), fp);
            save_connected_weights(*(l.ug), fp);
        } if (l.type == GRU) {
            if(1){
                save_connected_weights(*(l.wz), fp);
                save_connected_weights(*(l.wr), fp);
                save_connected_weights(*(l.wh), fp);
                save_connected_weights(*(l.uz), fp);
                save_connected_weights(*(l.ur), fp);
                save_connected_weights(*(l.uh), fp);
            }else{
                save_connected_weights(*(l.reset_layer), fp);
                save_connected_weights(*(l.update_layer), fp);
                save_connected_weights(*(l.state_layer), fp);
            }
        }  if(l.type == CRNN){
            save_convolutional_weights(*(l.input_layer), fp);
            save_convolutional_weights(*(l.self_layer), fp);
            save_convolutional_weights(*(l.output_layer), fp);
        } if(l.type == LOCAL){
#ifdef GPU
            if(gpu_index >= 0){
                pull_local_layer(l);
            }
#endif
            int locations = l.out_w*l.out_h;
            int size = l.size*l.size*l.c*l.n*locations;
            fwrite(l.biases, sizeof(float), l.outputs, fp);
            fwrite(l.weights, sizeof(float), size, fp);
        }
    }
    fclose(fp);
}