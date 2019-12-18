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
struct amba_kmi_port {int /*<<< orphan*/  io; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 struct amba_kmi_port* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  serio_reconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amba_kmi_resume(struct amba_device *dev)
{
	struct amba_kmi_port *kmi = amba_get_drvdata(dev);

	/* kick the serio layer to rescan this port */
	serio_reconnect(kmi->io);

	return 0;
}