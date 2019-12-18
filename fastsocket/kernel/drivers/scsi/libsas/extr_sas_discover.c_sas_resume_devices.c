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
struct work_struct {int dummy; } ;
struct sas_discovery_event {struct asd_sas_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending; } ;
struct asd_sas_port {TYPE_1__ disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_RESUME ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_resume_sata (struct asd_sas_port*) ; 
 struct sas_discovery_event* to_sas_discovery_event (struct work_struct*) ; 

__attribute__((used)) static void sas_resume_devices(struct work_struct *work)
{
	struct sas_discovery_event *ev = to_sas_discovery_event(work);
	struct asd_sas_port *port = ev->port;

	clear_bit(DISCE_RESUME, &port->disc.pending);

	sas_resume_sata(port);
}