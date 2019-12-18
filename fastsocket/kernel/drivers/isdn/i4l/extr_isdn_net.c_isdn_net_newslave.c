#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_1__* local; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_5__ {scalar_t__ master; } ;

/* Variables and functions */
 scalar_t__ isdn_net_device_started (TYPE_2__*) ; 
 TYPE_2__* isdn_net_findif (char*) ; 
 char* isdn_net_new (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

char *
isdn_net_newslave(char *parm)
{
	char *p = strchr(parm, ',');
	isdn_net_dev *n;
	char newname[10];

	if (p) {
		/* Slave-Name MUST not be empty */
		if (!strlen(p + 1))
			return NULL;
		strcpy(newname, p + 1);
		*p = 0;
		/* Master must already exist */
		if (!(n = isdn_net_findif(parm)))
			return NULL;
		/* Master must be a real interface, not a slave */
		if (n->local->master)
			return NULL;
		/* Master must not be started yet */
		if (isdn_net_device_started(n)) 
			return NULL;
		return (isdn_net_new(newname, n->dev));
	}
	return NULL;
}