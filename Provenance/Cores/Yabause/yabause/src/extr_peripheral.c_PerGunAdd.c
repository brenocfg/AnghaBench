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
typedef  int /*<<< orphan*/  PortData_struct ;
typedef  int /*<<< orphan*/  PerGun_struct ;

/* Variables and functions */
 int /*<<< orphan*/  PERGUN ; 
 int /*<<< orphan*/ * PerAddPeripheral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PerGun_struct * PerGunAdd(PortData_struct * port)
{
   return PerAddPeripheral(port, PERGUN);
}