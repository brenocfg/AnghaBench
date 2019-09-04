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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  eg_cache ; 
 int /*<<< orphan*/  el_cache ; 
 int /*<<< orphan*/  mcache_reap_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
eventhandler_reap_caches(boolean_t purge)
{
	mcache_reap_now(eg_cache, purge);
	mcache_reap_now(el_cache, purge);
}