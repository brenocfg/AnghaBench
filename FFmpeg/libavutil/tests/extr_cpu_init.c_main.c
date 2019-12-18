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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  thread_main ; 

int main(void)
{
    int cpu_flags1;
    int cpu_flags2;
    int ret;
    pthread_t thread1;
    pthread_t thread2;

    if ((ret = pthread_create(&thread1, NULL, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        return 1;
    }
    if ((ret = pthread_create(&thread2, NULL, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        return 1;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if (cpu_flags1 < 0)
        return 2;
    if (cpu_flags2 < 0)
        return 2;
    if (cpu_flags1 != cpu_flags2)
        return 3;

    return 0;
}