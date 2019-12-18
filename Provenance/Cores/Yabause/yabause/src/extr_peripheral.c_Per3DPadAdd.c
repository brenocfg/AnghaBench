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
typedef  int /*<<< orphan*/  PerAnalog_struct ;

/* Variables and functions */
 int /*<<< orphan*/  PER3DPAD ; 
 int /*<<< orphan*/ * PerAddPeripheral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PerAnalog_struct * Per3DPadAdd(PortData_struct * port)
{
   return PerAddPeripheral(port, PER3DPAD);
}