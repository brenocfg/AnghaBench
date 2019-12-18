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
struct nilfs_transaction_info {unsigned int ti_flags; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 TYPE_1__* current ; 

__attribute__((used)) static inline void nilfs_set_transaction_flag(unsigned int flag)
{
	struct nilfs_transaction_info *ti = current->journal_info;

	ti->ti_flags |= flag;
}