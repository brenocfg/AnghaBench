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
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  ff_lock_avformat () ; 
 int /*<<< orphan*/  ff_unlock_avformat () ; 
 int /*<<< orphan*/  openssl_init ; 

int ff_openssl_init(void)
{
    ff_lock_avformat();
    if (!openssl_init) {
        SSL_library_init();
        SSL_load_error_strings();
#if HAVE_THREADS
        if (!CRYPTO_get_locking_callback()) {
            int i;
            openssl_mutexes = av_malloc_array(sizeof(pthread_mutex_t), CRYPTO_num_locks());
            if (!openssl_mutexes) {
                ff_unlock_avformat();
                return AVERROR(ENOMEM);
            }

            for (i = 0; i < CRYPTO_num_locks(); i++)
                pthread_mutex_init(&openssl_mutexes[i], NULL);
            CRYPTO_set_locking_callback(openssl_lock);
#if !defined(WIN32) && OPENSSL_VERSION_NUMBER < 0x10000000
            CRYPTO_set_id_callback(openssl_thread_id);
#endif
        }
#endif
    }
    openssl_init++;
    ff_unlock_avformat();

    return 0;
}