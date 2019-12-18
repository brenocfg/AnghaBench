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
typedef  int (* ofw_handle_t ) (unsigned int*) ;

/* Variables and functions */

int
OF_finddevice(ofw_handle_t openfirmware, char *name)
{
	unsigned int args[8];
	char service[12];

	service[0]='f';
	service[1]='i';
	service[2]='n';
	service[3]='d';
	service[4]='d';
	service[5]='e';
	service[6]='v';
	service[7]='i';
	service[8]='c';
	service[9]='e';
	service[10]='\0';

	args[0]=(unsigned int)service;
	args[1]=1;
	args[2]=1;
	args[3]=(unsigned int)name;

	if (openfirmware(args) == -1)
		return -1;
	return args[4];
}