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
 int /*<<< orphan*/  GCRYCTL_ANY_INITIALIZATION_P ; 
 int /*<<< orphan*/  GCRYCTL_SET_THREAD_CBS ; 
 int /*<<< orphan*/  ff_lock_avformat () ; 
 int /*<<< orphan*/  ff_unlock_avformat () ; 
 scalar_t__ gcry_control (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gcry_threads_pthread ; 
 int /*<<< orphan*/  gnutls_global_init () ; 

void ff_gnutls_init(void)
{
    ff_lock_avformat();
#if HAVE_THREADS && GNUTLS_VERSION_NUMBER < 0x020b00
    if (gcry_control(GCRYCTL_ANY_INITIALIZATION_P) == 0)
        gcry_control(GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);
#endif
    gnutls_global_init();
    ff_unlock_avformat();
}