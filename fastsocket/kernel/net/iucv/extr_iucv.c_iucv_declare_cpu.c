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
struct TYPE_2__ {int /*<<< orphan*/  ipbfadr1; } ;
union iucv_param {TYPE_1__ db; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_DECLARE_BUFFER ; 
 scalar_t__ cpu_isset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_set (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_allow_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_block_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 int /*<<< orphan*/ * iucv_irq_data ; 
 scalar_t__ iucv_nonsmp_handler ; 
 union iucv_param** iucv_param_irq ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int,char*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iucv_declare_cpu(void *data)
{
	int cpu = smp_processor_id();
	union iucv_param *parm;
	int rc;

	if (cpu_isset(cpu, iucv_buffer_cpumask))
		return;

	/* Declare interrupt buffer. */
	parm = iucv_param_irq[cpu];
	memset(parm, 0, sizeof(union iucv_param));
	parm->db.ipbfadr1 = virt_to_phys(iucv_irq_data[cpu]);
	rc = iucv_call_b2f0(IUCV_DECLARE_BUFFER, parm);
	if (rc) {
		char *err = "Unknown";
		switch (rc) {
		case 0x03:
			err = "Directory error";
			break;
		case 0x0a:
			err = "Invalid length";
			break;
		case 0x13:
			err = "Buffer already exists";
			break;
		case 0x3e:
			err = "Buffer overlap";
			break;
		case 0x5c:
			err = "Paging or storage error";
			break;
		}
		pr_warning("Defining an interrupt buffer on CPU %i"
			   " failed with 0x%02x (%s)\n", cpu, rc, err);
		return;
	}

	/* Set indication that an iucv buffer exists for this cpu. */
	cpu_set(cpu, iucv_buffer_cpumask);

	if (iucv_nonsmp_handler == 0 || cpus_empty(iucv_irq_cpumask))
		/* Enable iucv interrupts on this cpu. */
		iucv_allow_cpu(NULL);
	else
		/* Disable iucv interrupts on this cpu. */
		iucv_block_cpu(NULL);
}