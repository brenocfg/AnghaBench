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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lockOrExit(char* className, pthread_mutex_t* mut)
{
    int result = pthread_mutex_lock(mut);
    if (0 != result) {
        printf("Error locking mutex in %s: %i\n", className, result);
        exit(1);
    }
//    else { printf("SUCCESSFUL mutex lock in %s\n", className); }
}