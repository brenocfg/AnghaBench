#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int learning_rate; double momentum; double decay; int* seen; int max_batches; int batch; int subdivisions; } ;
typedef  TYPE_1__ network ;
struct TYPE_14__ {int n; } ;
typedef  TYPE_2__ moves ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 char* basecfg (char*) ; 
 TYPE_1__** calloc (int,int) ; 
 int /*<<< orphan*/  cuda_set_device (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_network (TYPE_1__*) ; 
 int get_current_batch (TYPE_1__*) ; 
 int /*<<< orphan*/  get_current_rate (TYPE_1__*) ; 
 TYPE_2__ load_go_moves (char*) ; 
 TYPE_1__* load_network (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  random_go_moves (TYPE_2__,int) ; 
 int /*<<< orphan*/  save_weights (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  srand (int) ; 
 int time (int /*<<< orphan*/ ) ; 
 float train_network (TYPE_1__*,int /*<<< orphan*/ ) ; 
 float train_networks (TYPE_1__**,int,int /*<<< orphan*/ ,int) ; 
 double what_time_is_it_now () ; 

void train_go(char *cfgfile, char *weightfile, char *filename, int *gpus, int ngpus, int clear)
{
    int i;
    float avg_loss = -1;
    char *base = basecfg(cfgfile);
    printf("%s\n", base);
    printf("%d\n", ngpus);
    network **nets = calloc(ngpus, sizeof(network*));

    srand(time(0));
    int seed = rand();
    for(i = 0; i < ngpus; ++i){
        srand(seed);
#ifdef GPU
        cuda_set_device(gpus[i]);
#endif
        nets[i] = load_network(cfgfile, weightfile, clear);
        nets[i]->learning_rate *= ngpus;
    }
    network *net = nets[0];
    printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate, net->momentum, net->decay);

    char *backup_directory = "/home/pjreddie/backup/";

    char buff[256];
    moves m = load_go_moves(filename);
    //moves m = load_go_moves("games.txt");

    int N = m.n;
    printf("Moves: %d\n", N);
    int epoch = (*net->seen)/N;
    while(get_current_batch(net) < net->max_batches || net->max_batches == 0){
        double time=what_time_is_it_now();

        data train = random_go_moves(m, net->batch*net->subdivisions*ngpus);
        printf("Loaded: %lf seconds\n", what_time_is_it_now() - time);
        time=what_time_is_it_now();

        float loss = 0;
#ifdef GPU
        if(ngpus == 1){
            loss = train_network(net, train);
        } else {
            loss = train_networks(nets, ngpus, train, 10);
        }
#else
        loss = train_network(net, train);
#endif
        free_data(train);

        if(avg_loss == -1) avg_loss = loss;
        avg_loss = avg_loss*.95 + loss*.05;
        printf("%ld, %.3f: %f, %f avg, %f rate, %lf seconds, %ld images\n", get_current_batch(net), (float)(*net->seen)/N, loss, avg_loss, get_current_rate(net), what_time_is_it_now()-time, *net->seen);
        if(*net->seen/N > epoch){
            epoch = *net->seen/N;
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights", backup_directory,base, epoch);
            save_weights(net, buff);

        }
        if(get_current_batch(net)%1000 == 0){
            char buff[256];
            sprintf(buff, "%s/%s.backup",backup_directory,base);
            save_weights(net, buff);
        }
        if(get_current_batch(net)%10000 == 0){
            char buff[256];
            sprintf(buff, "%s/%s_%ld.backup",backup_directory,base,get_current_batch(net));
            save_weights(net, buff);
        }
    }
    sprintf(buff, "%s/%s.weights", backup_directory, base);
    save_weights(net, buff);

    free_network(net);
    free(base);
}