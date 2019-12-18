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
typedef  int u8 ;
struct amd64_pvt {int ext_model; int /*<<< orphan*/  mc_node_id; int /*<<< orphan*/ * ops; } ;
struct amd64_family_type {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  ops; } ;
struct TYPE_2__ {int x86; int x86_model; } ;

/* Variables and functions */
 size_t F10_CPUS ; 
 size_t F15_CPUS ; 
 size_t F16_CPUS ; 
 size_t K8_CPUS ; 
 int K8_REV_F ; 
 int /*<<< orphan*/  amd64_err (char*) ; 
 struct amd64_family_type* amd64_family_types ; 
 int /*<<< orphan*/  amd64_info (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static struct amd64_family_type *amd64_per_family_init(struct amd64_pvt *pvt)
{
	u8 fam = boot_cpu_data.x86;
	struct amd64_family_type *fam_type = NULL;

	switch (fam) {
	case 0xf:
		fam_type		= &amd64_family_types[K8_CPUS];
		pvt->ops		= &amd64_family_types[K8_CPUS].ops;
		break;

	case 0x10:
		fam_type		= &amd64_family_types[F10_CPUS];
		pvt->ops		= &amd64_family_types[F10_CPUS].ops;
		break;

	case 0x15:
		fam_type		= &amd64_family_types[F15_CPUS];
		pvt->ops		= &amd64_family_types[F15_CPUS].ops;
		break;

	case 0x16:
		fam_type		= &amd64_family_types[F16_CPUS];
		pvt->ops		= &amd64_family_types[F16_CPUS].ops;
		break;

	default:
		amd64_err("Unsupported family!\n");
		return NULL;
	}

	pvt->ext_model = boot_cpu_data.x86_model >> 4;

	amd64_info("%s %sdetected (node %d).\n", fam_type->ctl_name,
		     (fam == 0xf ?
				(pvt->ext_model >= K8_REV_F  ? "revF or later "
							     : "revE or earlier ")
				 : ""), pvt->mc_node_id);
	return fam_type;
}