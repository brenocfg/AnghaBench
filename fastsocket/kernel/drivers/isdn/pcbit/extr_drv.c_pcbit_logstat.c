#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcbit_dev {TYPE_1__* dev_if; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int arg; int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_2__ isdn_ctrl ;
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_STAVAIL ; 
 int STATBUF_LEN ; 
 int stat_end ; 
 int stat_st ; 
 char* statbuf ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void pcbit_logstat(struct pcbit_dev *dev, char *str)
{
	int i;
	isdn_ctrl ictl;

	for (i=stat_end; i<strlen(str); i++)
	{
		statbuf[i]=str[i];
		stat_end = (stat_end + 1) % STATBUF_LEN;
		if (stat_end == stat_st)
			stat_st = (stat_st + 1) % STATBUF_LEN;
	}

	ictl.command=ISDN_STAT_STAVAIL;
	ictl.driver=dev->id;
	ictl.arg=strlen(str);
	dev->dev_if->statcallb(&ictl);
}