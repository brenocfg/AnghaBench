#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ;TYPE_3__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {void* MAC8; void* MAC7; } ;
struct TYPE_7__ {void* MAC6; void* MAC3; void* MAC2; void* MAC1; } ;
struct TYPE_9__ {TYPE_2__ mac_address_41c; TYPE_1__ mac_address_418; } ;
typedef  TYPE_3__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  mac_address_418 ; 
 int /*<<< orphan*/  mac_address_41c ; 
 TYPE_3__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  stub3 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 

void flexcop_set_mac_filter(struct flexcop_device *fc, u8 mac[6])
{
	flexcop_ibi_value v418, v41c;
	v41c = fc->read_ibi_reg(fc, mac_address_41c);

	v418.mac_address_418.MAC1 = mac[0];
	v418.mac_address_418.MAC2 = mac[1];
	v418.mac_address_418.MAC3 = mac[2];
	v418.mac_address_418.MAC6 = mac[3];
	v41c.mac_address_41c.MAC7 = mac[4];
	v41c.mac_address_41c.MAC8 = mac[5];

	fc->write_ibi_reg(fc, mac_address_418, v418);
	fc->write_ibi_reg(fc, mac_address_41c, v41c);
}