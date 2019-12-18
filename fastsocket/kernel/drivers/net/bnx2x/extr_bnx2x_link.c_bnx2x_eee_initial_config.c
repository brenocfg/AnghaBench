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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct link_vars {int eee_status; } ;
struct link_params {int eee_mode; } ;

/* Variables and functions */
 int EEE_MODE_ADV_LPI ; 
 int EEE_MODE_ENABLE_LPI ; 
 int SHMEM_EEE_LPI_REQUESTED_BIT ; 
 int SHMEM_EEE_REQUESTED_BIT ; 
 int SHMEM_EEE_SUPPORTED_SHIFT ; 
 int bnx2x_eee_set_timers (struct link_params*,struct link_vars*) ; 

__attribute__((used)) static int bnx2x_eee_initial_config(struct link_params *params,
				     struct link_vars *vars, u8 mode)
{
	vars->eee_status |= ((u32) mode) << SHMEM_EEE_SUPPORTED_SHIFT;

	/* Propogate params' bits --> vars (for migration exposure) */
	if (params->eee_mode & EEE_MODE_ENABLE_LPI)
		vars->eee_status |= SHMEM_EEE_LPI_REQUESTED_BIT;
	else
		vars->eee_status &= ~SHMEM_EEE_LPI_REQUESTED_BIT;

	if (params->eee_mode & EEE_MODE_ADV_LPI)
		vars->eee_status |= SHMEM_EEE_REQUESTED_BIT;
	else
		vars->eee_status &= ~SHMEM_EEE_REQUESTED_BIT;

	return bnx2x_eee_set_timers(params, vars);
}