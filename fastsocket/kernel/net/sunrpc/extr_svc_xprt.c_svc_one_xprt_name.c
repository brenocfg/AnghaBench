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
struct svc_xprt {TYPE_1__* xpt_class; } ;
struct TYPE_2__ {char* xcl_name; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int snprintf (char*,int,char*,char*,int) ; 
 int svc_xprt_local_port (struct svc_xprt const*) ; 

__attribute__((used)) static int svc_one_xprt_name(const struct svc_xprt *xprt,
			     char *pos, int remaining)
{
	int len;

	len = snprintf(pos, remaining, "%s %u\n",
			xprt->xpt_class->xcl_name,
			svc_xprt_local_port(xprt));
	if (len >= remaining)
		return -ENAMETOOLONG;
	return len;
}