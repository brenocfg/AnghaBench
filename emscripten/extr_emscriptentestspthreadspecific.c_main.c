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
 int EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destr_function ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* pthread_getspecific (int /*<<< orphan*/ ) ; 
 int pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_key_delete (int /*<<< orphan*/ ) ; 
 int pthread_setspecific (int /*<<< orphan*/ ,void*) ; 

int main(void)
{
    pthread_key_t key = 0;
    int rv;
    int data = 123;
    int *data2;

    assert(pthread_key_delete(key) != 0);
    assert(pthread_getspecific(key) == NULL);

    rv = pthread_key_create(&key, &destr_function);
    printf("pthread_key_create = %d\n", rv);
    assert(rv == 0);

    assert(pthread_getspecific(key) == NULL);

    rv = pthread_setspecific(key, (void*) &data);
    printf("pthread_setspecific = %d\n", rv);
    assert(rv == 0);

    data2 = pthread_getspecific(key);
    assert(data2 != NULL);
    printf("pthread_getspecific = %d\n", *data2);
    assert(*data2 == 123);

    rv = pthread_setspecific(key, NULL);
    printf("valid pthread_setspecific for value NULL = %d\n", rv);
    assert(rv == 0);

    data2 = pthread_getspecific(key);
    assert(data2 == NULL);
    printf("pthread_getspecific = %p\n", data2);

    rv = pthread_key_create(&key, &destr_function);
    data2 = pthread_getspecific(key);
    printf("pthread_getspecific after key recreate = %p\n", data2);
    assert(data2 == NULL);

    rv = pthread_key_delete(key);
    printf("pthread_key_delete = %d\n", rv);
    assert(rv == 0);

    rv = pthread_key_delete(key);
    printf("pthread_key_delete repeated = %d\n", rv);
    assert(rv == EINVAL);

    rv = pthread_setspecific(key, NULL);
    printf("pthread_setspecific for value NULL = %d\n", rv);
    assert(rv == EINVAL);

    rv = pthread_key_create(&key, &destr_function);
    assert(rv == 0);
    rv = pthread_key_delete(key);
    printf("pthread_key_delete just after created = %d\n", rv);
    assert(rv == 0);

    return 0;
}