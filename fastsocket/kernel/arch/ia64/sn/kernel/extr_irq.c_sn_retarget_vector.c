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
typedef  scalar_t__ u64 ;
struct sn_pcibus_provider {int /*<<< orphan*/  (* target_interrupt ) (struct sn_irq_info*) ;} ;
struct sn_irq_info {int irq_irq; int irq_cpuid; size_t irq_bridge_type; scalar_t__ irq_int_bit; int /*<<< orphan*/  irq_slice; int /*<<< orphan*/  irq_nasid; int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; scalar_t__ irq_bridge; } ;
typedef  int nasid_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NASID_GET (scalar_t__) ; 
 int SWIN_WIDGETNUM (scalar_t__) ; 
 int TIO_SWIN_WIDGETNUM (scalar_t__) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cpu_physical_id (int) ; 
 int /*<<< orphan*/  kfree (struct sn_irq_info*) ; 
 struct sn_irq_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct sn_irq_info*,struct sn_irq_info*,int) ; 
 int nasid_slice_to_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_intr_pda (struct sn_irq_info*) ; 
 int /*<<< orphan*/  set_irq_affinity_info (int,int,int /*<<< orphan*/ ) ; 
 int sn_intr_alloc (int,int,struct sn_irq_info*,int,int,int) ; 
 int /*<<< orphan*/  sn_intr_free (int,int,struct sn_irq_info*) ; 
 int sn_intr_redirect (int,int,struct sn_irq_info*,int,int) ; 
 int /*<<< orphan*/  sn_irq_info_free ; 
 int /*<<< orphan*/  sn_irq_info_lock ; 
 struct sn_pcibus_provider** sn_pci_provider ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sn_irq_info*) ; 
 int /*<<< orphan*/  unregister_intr_pda (struct sn_irq_info*) ; 

struct sn_irq_info *sn_retarget_vector(struct sn_irq_info *sn_irq_info,
				       nasid_t nasid, int slice)
{
	int vector;
	int cpuid;
#ifdef CONFIG_SMP
	int cpuphys;
#endif
	int64_t bridge;
	int local_widget, status;
	nasid_t local_nasid;
	struct sn_irq_info *new_irq_info;
	struct sn_pcibus_provider *pci_provider;

	bridge = (u64) sn_irq_info->irq_bridge;
	if (!bridge) {
		return NULL; /* irq is not a device interrupt */
	}

	local_nasid = NASID_GET(bridge);

	if (local_nasid & 1)
		local_widget = TIO_SWIN_WIDGETNUM(bridge);
	else
		local_widget = SWIN_WIDGETNUM(bridge);
	vector = sn_irq_info->irq_irq;

	/* Make use of SAL_INTR_REDIRECT if PROM supports it */
	status = sn_intr_redirect(local_nasid, local_widget, sn_irq_info, nasid, slice);
	if (!status) {
		new_irq_info = sn_irq_info;
		goto finish_up;
	}

	/*
	 * PROM does not support SAL_INTR_REDIRECT, or it failed.
	 * Revert to old method.
	 */
	new_irq_info = kmalloc(sizeof(struct sn_irq_info), GFP_ATOMIC);
	if (new_irq_info == NULL)
		return NULL;

	memcpy(new_irq_info, sn_irq_info, sizeof(struct sn_irq_info));

	/* Free the old PROM new_irq_info structure */
	sn_intr_free(local_nasid, local_widget, new_irq_info);
	unregister_intr_pda(new_irq_info);

	/* allocate a new PROM new_irq_info struct */
	status = sn_intr_alloc(local_nasid, local_widget,
			       new_irq_info, vector,
			       nasid, slice);

	/* SAL call failed */
	if (status) {
		kfree(new_irq_info);
		return NULL;
	}

	register_intr_pda(new_irq_info);
	spin_lock(&sn_irq_info_lock);
	list_replace_rcu(&sn_irq_info->list, &new_irq_info->list);
	spin_unlock(&sn_irq_info_lock);
	call_rcu(&sn_irq_info->rcu, sn_irq_info_free);


finish_up:
	/* Update kernels new_irq_info with new target info */
	cpuid = nasid_slice_to_cpuid(new_irq_info->irq_nasid,
				     new_irq_info->irq_slice);
	new_irq_info->irq_cpuid = cpuid;

	pci_provider = sn_pci_provider[new_irq_info->irq_bridge_type];

	/*
	 * If this represents a line interrupt, target it.  If it's
	 * an msi (irq_int_bit < 0), it's already targeted.
	 */
	if (new_irq_info->irq_int_bit >= 0 &&
	    pci_provider && pci_provider->target_interrupt)
		(pci_provider->target_interrupt)(new_irq_info);

#ifdef CONFIG_SMP
	cpuphys = cpu_physical_id(cpuid);
	set_irq_affinity_info((vector & 0xff), cpuphys, 0);
#endif

	return new_irq_info;
}