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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {TYPE_1__* extif; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_data ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* write_command ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* set_bits_per_cycle ) (int) ;} ;

/* Variables and functions */
 TYPE_2__ blizzard ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 blizzard_read_reg(u8 reg)
{
	u8 data;

	blizzard.extif->set_bits_per_cycle(8);
	blizzard.extif->write_command(&reg, 1);
	blizzard.extif->read_data(&data, 1);

	return data;
}