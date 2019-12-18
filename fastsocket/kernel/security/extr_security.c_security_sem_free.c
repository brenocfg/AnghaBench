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
struct TYPE_2__ {int /*<<< orphan*/  (* sem_free_security ) (struct sem_array*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct sem_array*) ; 

void security_sem_free(struct sem_array *sma)
{
	security_ops->sem_free_security(sma);
}