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
typedef  int /*<<< orphan*/  sys_prot_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_lwip_protect_mutex ; 
 int /*<<< orphan*/  sys_mutex_lock (int /*<<< orphan*/ *) ; 

sys_prot_t
sys_arch_protect(void)
{
  sys_mutex_lock(&g_lwip_protect_mutex);
  return (sys_prot_t) 1;
}