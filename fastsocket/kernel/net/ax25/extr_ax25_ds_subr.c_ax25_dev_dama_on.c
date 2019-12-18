#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int slave; } ;
struct TYPE_7__ {TYPE_1__ dama; } ;
typedef  TYPE_2__ ax25_dev ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_ds_set_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_kiss_cmd (TYPE_2__*,int,int) ; 

__attribute__((used)) static void ax25_dev_dama_on(ax25_dev *ax25_dev)
{
	if (ax25_dev == NULL)
		return;

	if (ax25_dev->dama.slave == 0)
		ax25_kiss_cmd(ax25_dev, 5, 1);

	ax25_dev->dama.slave = 1;
	ax25_ds_set_timer(ax25_dev);
}