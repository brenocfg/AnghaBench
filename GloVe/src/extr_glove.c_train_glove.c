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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int real ;
typedef  long long pthread_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CREC ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  alpha ; 
 int checkpoint_every ; 
 scalar_t__* cost ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (long long*) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long ftello (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glove_thread ; 
 int /*<<< orphan*/  initialize_parameters () ; 
 char* input_file ; 
 long long* lines_per_thread ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int num_iter ; 
 int num_lines ; 
 int num_threads ; 
 int /*<<< orphan*/  pthread_create (long long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_join (long long,int /*<<< orphan*/ *) ; 
 int save_params (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int vector_size ; 
 int verbose ; 
 int /*<<< orphan*/  vocab_size ; 
 int /*<<< orphan*/  x_max ; 

int train_glove() {
    long long a, file_size;
    int save_params_return_code;
    int b;
    FILE *fin;
    real total_cost = 0;

    fprintf(stderr, "TRAINING MODEL\n");
    
    fin = fopen(input_file, "rb");
    if (fin == NULL) {fprintf(stderr,"Unable to open cooccurrence file %s.\n",input_file); return 1;}
    fseeko(fin, 0, SEEK_END);
    file_size = ftello(fin);
    num_lines = file_size/(sizeof(CREC)); // Assuming the file isn't corrupt and consists only of CREC's
    fclose(fin);
    fprintf(stderr,"Read %lld lines.\n", num_lines);
    if (verbose > 1) fprintf(stderr,"Initializing parameters...");
    initialize_parameters();
    if (verbose > 1) fprintf(stderr,"done.\n");
    if (verbose > 0) fprintf(stderr,"vector size: %d\n", vector_size);
    if (verbose > 0) fprintf(stderr,"vocab size: %lld\n", vocab_size);
    if (verbose > 0) fprintf(stderr,"x_max: %lf\n", x_max);
    if (verbose > 0) fprintf(stderr,"alpha: %lf\n", alpha);
    pthread_t *pt = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    lines_per_thread = (long long *) malloc(num_threads * sizeof(long long));
    
    time_t rawtime;
    struct tm *info;
    char time_buffer[80];
    // Lock-free asynchronous SGD
    for (b = 0; b < num_iter; b++) {
        total_cost = 0;
        for (a = 0; a < num_threads - 1; a++) lines_per_thread[a] = num_lines / num_threads;
        lines_per_thread[a] = num_lines / num_threads + num_lines % num_threads;
        long long *thread_ids = (long long*)malloc(sizeof(long long) * num_threads);
        for (a = 0; a < num_threads; a++) thread_ids[a] = a;
        for (a = 0; a < num_threads; a++) pthread_create(&pt[a], NULL, glove_thread, (void *)&thread_ids[a]);
        for (a = 0; a < num_threads; a++) pthread_join(pt[a], NULL);
        for (a = 0; a < num_threads; a++) total_cost += cost[a];
        free(thread_ids);

        time(&rawtime);
        info = localtime(&rawtime);
        strftime(time_buffer,80,"%x - %I:%M.%S%p", info);
        fprintf(stderr, "%s, iter: %03d, cost: %lf\n", time_buffer,  b+1, total_cost/num_lines);

        if (checkpoint_every > 0 && (b + 1) % checkpoint_every == 0) {
            fprintf(stderr,"    saving itermediate parameters for iter %03d...", b+1);
            save_params_return_code = save_params(b+1);
            if (save_params_return_code != 0)
                return save_params_return_code;
            fprintf(stderr,"done.\n");
        }

    }
    free(pt);
    free(lines_per_thread);
    return save_params(0);
}