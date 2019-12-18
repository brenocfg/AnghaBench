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
struct pcbit_chan {int /*<<< orphan*/  id; } ;
struct callb_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_2__ isdn_ctrl ;
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_BCONN ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void cb_open(struct pcbit_dev * dev, struct pcbit_chan* chan, 
	     struct callb_data *data) 
{
        isdn_ctrl ictl;

        ictl.command = ISDN_STAT_BCONN;
        ictl.driver=dev->id;
        ictl.arg=chan->id;
        dev->dev_if->statcallb(&ictl);
}