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

/* Variables and functions */
 int ENOMEM ; 
 char* strdup (char*) ; 

int
devid_get_minor_name(int fd, char **retminor_name)
{

	*retminor_name = strdup("");
	if (*retminor_name == NULL)
		return (ENOMEM);
	return (0);
}