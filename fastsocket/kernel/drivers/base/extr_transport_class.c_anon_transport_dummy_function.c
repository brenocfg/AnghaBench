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
struct transport_container {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int anon_transport_dummy_function(struct transport_container *tc,
					 struct device *dev,
					 struct device *cdev)
{
	/* do nothing */
	return 0;
}