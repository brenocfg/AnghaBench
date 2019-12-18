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
struct TYPE_2__ {int (* getprop ) (void*,char const*,void*,int) ;} ;

/* Variables and functions */
 TYPE_1__ dt_ops ; 
 int stub1 (void*,char const*,void*,int) ; 

__attribute__((used)) static inline int getprop(void *devp, const char *name, void *buf, int buflen)
{
	return (dt_ops.getprop) ? dt_ops.getprop(devp, name, buf, buflen) : -1;
}