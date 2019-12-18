#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* setprop ) (void*,char const*,char const*,scalar_t__) ;} ;

/* Variables and functions */
 TYPE_1__ dt_ops ; 
 scalar_t__ strlen (char const*) ; 
 int stub1 (void*,char const*,char const*,scalar_t__) ; 

__attribute__((used)) static inline int setprop_str(void *devp, const char *name, const char *buf)
{
	if (dt_ops.setprop)
		return dt_ops.setprop(devp, name, buf, strlen(buf) + 1);

	return -1;
}