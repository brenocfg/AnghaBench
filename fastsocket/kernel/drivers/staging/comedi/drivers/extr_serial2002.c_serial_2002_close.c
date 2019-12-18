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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  filp_close (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial_2002_close(struct comedi_device *dev)
{
	if (!IS_ERR(devpriv->tty) && (devpriv->tty != 0)) {
		filp_close(devpriv->tty, 0);
	}
}