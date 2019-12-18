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
struct sem_array {int dummy; } ;
struct TYPE_2__ {int (* sem_associate ) (struct sem_array*,int) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct sem_array*,int) ; 

int security_sem_associate(struct sem_array *sma, int semflg)
{
	return security_ops->sem_associate(sma, semflg);
}