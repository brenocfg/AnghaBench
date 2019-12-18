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
 scalar_t__ CRYPTO_get_locking_callback () ; 
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_lock_avformat () ; 
 int /*<<< orphan*/  ff_unlock_avformat () ; 
 int /*<<< orphan*/  openssl_init ; 
 scalar_t__ openssl_lock ; 
 int /*<<< orphan*/ * openssl_mutexes ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void ff_openssl_deinit(void)
{
    ff_lock_avformat();
    openssl_init--;
    if (!openssl_init) {
#if HAVE_THREADS
        if (CRYPTO_get_locking_callback() == openssl_lock) {
            int i;
            CRYPTO_set_locking_callback(NULL);
            for (i = 0; i < CRYPTO_num_locks(); i++)
                pthread_mutex_destroy(&openssl_mutexes[i]);
            av_free(openssl_mutexes);
        }
#endif
    }
    ff_unlock_avformat();
}