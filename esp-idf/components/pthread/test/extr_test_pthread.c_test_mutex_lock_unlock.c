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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int EDEADLK ; 
 int EPERM ; 
 int PTHREAD_MUTEX_ERRORCHECK ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_INT (int,int) ; 
 scalar_t__ TEST_PROTECT () ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutexattr_gettype (int /*<<< orphan*/ *,int*) ; 
 int pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int pthread_mutexattr_settype (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unlock_mutex ; 

__attribute__((used)) static void test_mutex_lock_unlock(int mutex_type)
{
    int res = 0;
    int set_type = -1;
    volatile bool attr_created = false;
    volatile bool mutex_created = false;
    volatile intptr_t thread_rval = 0;
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
    pthread_t new_thread;

    if (TEST_PROTECT()) {
        res = pthread_mutexattr_init(&attr);
        TEST_ASSERT_EQUAL_INT(0, res);
        attr_created = true;

        res = pthread_mutexattr_settype(&attr, mutex_type);
        TEST_ASSERT_EQUAL_INT(0, res);

        res = pthread_mutexattr_gettype(&attr, &set_type);
        TEST_ASSERT_EQUAL_INT(0, res);
        TEST_ASSERT_EQUAL_INT(mutex_type, set_type);

        res = pthread_mutex_init(&mutex, &attr);
        TEST_ASSERT_EQUAL_INT(0, res);
        mutex_created = true;

        res = pthread_mutex_lock(&mutex);
        TEST_ASSERT_EQUAL_INT(0, res);

        res = pthread_mutex_lock(&mutex);

        if(mutex_type == PTHREAD_MUTEX_ERRORCHECK) {
            TEST_ASSERT_EQUAL_INT(EDEADLK, res);
        } else {
            TEST_ASSERT_EQUAL_INT(0, res);

            res = pthread_mutex_unlock(&mutex);
            TEST_ASSERT_EQUAL_INT(0, res);
        }

        pthread_create(&new_thread, NULL, unlock_mutex, &mutex);

        pthread_join(new_thread, (void **) &thread_rval);
        TEST_ASSERT_EQUAL_INT(EPERM, (int) thread_rval);

        res = pthread_mutex_unlock(&mutex);
        TEST_ASSERT_EQUAL_INT(0, res);
    }

    if (attr_created) {
        pthread_mutexattr_destroy(&attr);
    }

    if (mutex_created) {
        pthread_mutex_destroy(&mutex);
    }
}