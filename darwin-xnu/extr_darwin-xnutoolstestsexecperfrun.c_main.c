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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int atoi (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char** newargv ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  work ; 

int main(int argc, char *argv[]) {

    int i, count, threadcount;
    int ret;
    pthread_t *threads;

    if (argc < 4) {
        usage();
    }

    threadcount = atoi(argv[1]);
    count = atoi(argv[2]);
    
    newargv = &argv[3];

    threads = (pthread_t *)calloc(threadcount, sizeof(pthread_t));
    for (i=0; i < threadcount; i++) {
        ret = pthread_create(&threads[i], NULL, work, (void *)(intptr_t)count);
        if (ret) {
            err(1, "pthread_create");
        }
    }
    
    for (i=0; i < threadcount; i++) {
        ret = pthread_join(threads[i], NULL);
        if (ret) {
            err(1, "pthread_join");
        }
    }
    
    return 0;
}