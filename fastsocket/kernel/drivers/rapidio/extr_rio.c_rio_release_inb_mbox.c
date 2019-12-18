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
struct rio_mport {TYPE_1__* inb_msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_close_inb_mbox (struct rio_mport*,int) ; 

int rio_release_inb_mbox(struct rio_mport *mport, int mbox)
{
	rio_close_inb_mbox(mport, mbox);

	/* Release the mailbox resource */
	return release_resource(mport->inb_msg[mbox].res);
}