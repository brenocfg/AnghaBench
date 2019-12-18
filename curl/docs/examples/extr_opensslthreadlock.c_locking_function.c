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
 int CRYPTO_LOCK ; 
 int /*<<< orphan*/  MUTEX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mutex_buf ; 

__attribute__((used)) static void locking_function(int mode, int n, const char *file, int line)
{
  if(mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}