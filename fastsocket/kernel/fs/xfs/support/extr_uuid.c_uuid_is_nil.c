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
typedef  int /*<<< orphan*/  uuid_t ;

/* Variables and functions */

int
uuid_is_nil(uuid_t *uuid)
{
	int	i;
	char	*cp = (char *)uuid;

	if (uuid == NULL)
		return 0;
	/* implied check of version number here... */
	for (i = 0; i < sizeof *uuid; i++)
		if (*cp++) return 0;	/* not nil */
	return 1;	/* is nil */
}