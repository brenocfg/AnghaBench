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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_hibernate; } ;

/* Variables and functions */
 TYPE_1__* cpu_datap (int) ; 

__attribute__((used)) static boolean_t
pmCPUGetHibernate(int cpu)
{
    return(cpu_datap(cpu)->cpu_hibernate);
}