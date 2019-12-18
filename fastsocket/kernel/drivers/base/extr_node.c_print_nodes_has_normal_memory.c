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
struct sysdev_class {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  N_NORMAL_MEMORY ; 
 int /*<<< orphan*/  print_nodes_state (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t print_nodes_has_normal_memory(struct sysdev_class *class,
						char *buf)
{
	return print_nodes_state(N_NORMAL_MEMORY, buf);
}