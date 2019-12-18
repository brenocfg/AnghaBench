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
struct shmid_kernel {int dummy; } ;
struct TYPE_2__ {int (* shm_alloc_security ) (struct shmid_kernel*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct shmid_kernel*) ; 

int security_shm_alloc(struct shmid_kernel *shp)
{
	return security_ops->shm_alloc_security(shp);
}