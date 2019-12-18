#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  devid; } ;
typedef  TYPE_1__ ddi_devid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 char* strdup (char*) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
devid_str_decode(char *devidstr, ddi_devid_t *retdevid, char **retminor_name)
{

	if (strlcpy(retdevid->devid, devidstr, sizeof(retdevid->devid)) >=
	    sizeof(retdevid->devid)) {
		return (EINVAL);
	}
	*retminor_name = strdup("");
	if (*retminor_name == NULL)
		return (ENOMEM);
	return (0);
}