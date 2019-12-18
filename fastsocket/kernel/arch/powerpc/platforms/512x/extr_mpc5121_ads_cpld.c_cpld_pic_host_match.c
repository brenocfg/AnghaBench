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
struct irq_host {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* cpld_pic_node ; 

__attribute__((used)) static int
cpld_pic_host_match(struct irq_host *h, struct device_node *node)
{
	return cpld_pic_node == node;
}