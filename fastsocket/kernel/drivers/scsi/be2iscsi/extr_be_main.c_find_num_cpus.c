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
struct beiscsi_hba {int generation; int num_cpus; } ;

/* Variables and functions */
 int BEISCSI_MAX_NUM_CPUS ; 
#define  BE_GEN2 130 
#define  BE_GEN3 129 
#define  BE_GEN4 128 
 int OC_SKH_MAX_NUM_CPUS ; 
 int num_online_cpus () ; 

__attribute__((used)) static void find_num_cpus(struct beiscsi_hba *phba)
{
	int  num_cpus = 0;

	num_cpus = num_online_cpus();

	switch (phba->generation) {
	case BE_GEN2:
	case BE_GEN3:
		phba->num_cpus = (num_cpus > BEISCSI_MAX_NUM_CPUS) ?
				  BEISCSI_MAX_NUM_CPUS : num_cpus;
		break;
	case BE_GEN4:
		phba->num_cpus = (num_cpus > OC_SKH_MAX_NUM_CPUS) ?
				  OC_SKH_MAX_NUM_CPUS : num_cpus;
		break;
	default:
		phba->num_cpus = 1;
	}
}