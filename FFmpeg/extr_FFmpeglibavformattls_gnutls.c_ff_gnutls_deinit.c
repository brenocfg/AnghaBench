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
 int /*<<< orphan*/  ff_lock_avformat () ; 
 int /*<<< orphan*/  ff_unlock_avformat () ; 
 int /*<<< orphan*/  gnutls_global_deinit () ; 

void ff_gnutls_deinit(void)
{
    ff_lock_avformat();
    gnutls_global_deinit();
    ff_unlock_avformat();
}