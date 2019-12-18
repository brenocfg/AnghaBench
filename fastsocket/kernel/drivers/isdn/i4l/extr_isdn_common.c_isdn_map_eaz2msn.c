#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** msn2eaz; } ;
typedef  TYPE_1__ isdn_driver_t ;
struct TYPE_4__ {TYPE_1__** drv; } ;

/* Variables and functions */
 TYPE_2__* dev ; 
 int strlen (char*) ; 

char *
isdn_map_eaz2msn(char *msn, int di)
{
	isdn_driver_t *this = dev->drv[di];
	int i;

	if (strlen(msn) == 1) {
		i = msn[0] - '0';
		if ((i >= 0) && (i <= 9))
			if (strlen(this->msn2eaz[i]))
				return (this->msn2eaz[i]);
	}
	return (msn);
}