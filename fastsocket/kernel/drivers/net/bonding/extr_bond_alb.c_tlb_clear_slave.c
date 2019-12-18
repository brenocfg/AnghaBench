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
struct slave {int dummy; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tlb_clear_slave (struct bonding*,struct slave*,int) ; 
 int /*<<< orphan*/  _lock_tx_hashtbl_bh (struct bonding*) ; 
 int /*<<< orphan*/  _unlock_tx_hashtbl_bh (struct bonding*) ; 

__attribute__((used)) static void tlb_clear_slave(struct bonding *bond, struct slave *slave,
			 int save_load)
{
	_lock_tx_hashtbl_bh(bond);
	__tlb_clear_slave(bond, slave, save_load);
	_unlock_tx_hashtbl_bh(bond);
}