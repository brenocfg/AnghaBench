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
 int /*<<< orphan*/  khrn_platform_free (scalar_t__) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  platform_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ workspace ; 

void rpc_term(void)
{
   if (workspace) { khrn_platform_free(workspace); }
   platform_mutex_destroy(&mutex);
}