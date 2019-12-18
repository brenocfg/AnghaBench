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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 void* llc_get_sk_idx (scalar_t__) ; 
 int /*<<< orphan*/  llc_sap_list_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *llc_seq_start(struct seq_file *seq, loff_t *pos)
{
	loff_t l = *pos;

	read_lock_bh(&llc_sap_list_lock);
	return l ? llc_get_sk_idx(--l) : SEQ_START_TOKEN;
}