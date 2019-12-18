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
typedef  int /*<<< orphan*/  pthread_key_t ;

/* Variables and functions */
 int /*<<< orphan*/ * expected_destructor_ptr ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *thread_test_pthread_destructor(void *v_key)
{
    printf("Local storage thread running...\n");
    pthread_key_t key = (pthread_key_t) v_key;
    expected_destructor_ptr = &key; // address of stack variable in the task...
    pthread_setspecific(key, expected_destructor_ptr);
    printf("Local storage thread done.\n");
    return NULL;
}