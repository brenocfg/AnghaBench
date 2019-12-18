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
typedef  int /*<<< orphan*/  MUTEX_TYPE ;

/* Variables and functions */
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_function ; 
 int /*<<< orphan*/  locking_function ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/ * mutex_buf ; 

int thread_setup(void)
{
  int i;

  mutex_buf = malloc(CRYPTO_num_locks() * sizeof(MUTEX_TYPE));
  if(!mutex_buf)
    return 0;
  for(i = 0;  i < CRYPTO_num_locks();  i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  return 1;
}