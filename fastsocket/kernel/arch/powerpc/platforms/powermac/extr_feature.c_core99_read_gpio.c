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
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 long MACIO_IN8 (long) ; 
 struct macio_chip* macio_chips ; 

__attribute__((used)) static long
core99_read_gpio(struct device_node *node, long param, long value)
{
	struct macio_chip *macio = &macio_chips[0];

	return MACIO_IN8(param);
}