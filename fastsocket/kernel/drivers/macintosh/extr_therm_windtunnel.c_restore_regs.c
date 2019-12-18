#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  r0; int /*<<< orphan*/  fan; int /*<<< orphan*/  r25; int /*<<< orphan*/  r23; int /*<<< orphan*/  r20; int /*<<< orphan*/  r1; TYPE_1__* of_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_case_temperature ; 
 int /*<<< orphan*/  dev_attr_cpu_temperature ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ x ; 

__attribute__((used)) static void
restore_regs( void )
{
	device_remove_file( &x.of_dev->dev, &dev_attr_cpu_temperature );
	device_remove_file( &x.of_dev->dev, &dev_attr_case_temperature );

	write_reg( x.fan, 0x01, x.r1, 1 );
	write_reg( x.fan, 0x20, x.r20, 1 );
	write_reg( x.fan, 0x23, x.r23, 1 );
	write_reg( x.fan, 0x25, x.r25, 1 );
	write_reg( x.fan, 0x00, x.r0, 1 );
}