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
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ehca_debug_level ; 

__attribute__((used)) static ssize_t ehca_store_debug_level(struct device_driver *ddp,
				      const char *buf, size_t count)
{
	int value = (*buf) - '0';
	if (value >= 0 && value <= 9)
		ehca_debug_level = value;
	return 1;
}