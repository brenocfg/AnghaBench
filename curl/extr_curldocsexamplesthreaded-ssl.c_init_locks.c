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
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (unsigned long (*) ()) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (void (*) ()) ; 
 scalar_t__ OPENSSL_malloc (int) ; 
 scalar_t__ lock_callback ; 
 int /*<<< orphan*/ * lockarray ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ thread_id ; 

__attribute__((used)) static void init_locks(void)
{
  int i;

  lockarray = (pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() *
                                                sizeof(pthread_mutex_t));
  for(i = 0; i<CRYPTO_num_locks(); i++) {
    pthread_mutex_init(&(lockarray[i]), NULL);
  }

  CRYPTO_set_id_callback((unsigned long (*)())thread_id);
  CRYPTO_set_locking_callback((void (*)())lock_callback);
}