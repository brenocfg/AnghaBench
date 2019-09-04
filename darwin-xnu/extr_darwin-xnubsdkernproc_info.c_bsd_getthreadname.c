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
struct uthread {scalar_t__ pth_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXTHREADNAMESIZE ; 
 int /*<<< orphan*/  bcopy (scalar_t__,char*,int /*<<< orphan*/ ) ; 

void 
bsd_getthreadname(void *uth, char *buffer)
{
	struct uthread *ut = (struct uthread *)uth;
	if(ut->pth_name)
		bcopy(ut->pth_name,buffer,MAXTHREADNAMESIZE);
}