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
typedef  int /*<<< orphan*/  dev_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 

boolean_t iskmemdev(dev_t dev)
{
	return (major(dev) == 3 && minor(dev) < 2);
}