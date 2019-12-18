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
typedef  int /*<<< orphan*/  PLATFORM_TLS_T ;

/* Variables and functions */
 void* platform_tls_get (int /*<<< orphan*/ ) ; 

void *platform_tls_get_check(PLATFORM_TLS_T tls)
{
   return platform_tls_get(tls);
}