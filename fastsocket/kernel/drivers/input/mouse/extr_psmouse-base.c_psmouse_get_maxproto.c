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
struct kernel_param {scalar_t__ arg; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 TYPE_1__* psmouse_protocol_by_type (int) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static int psmouse_get_maxproto(char *buffer, struct kernel_param *kp)
{
	int type = *((unsigned int *)kp->arg);

	return sprintf(buffer, "%s", psmouse_protocol_by_type(type)->name);
}