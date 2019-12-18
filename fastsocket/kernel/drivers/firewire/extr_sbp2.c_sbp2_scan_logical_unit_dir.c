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
typedef  int /*<<< orphan*/  u32 ;
struct sbp2_target {int dummy; } ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SBP2_CSR_LOGICAL_UNIT_NUMBER ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ *) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 scalar_t__ sbp2_add_logical_unit (struct sbp2_target*,int) ; 

__attribute__((used)) static int sbp2_scan_logical_unit_dir(struct sbp2_target *tgt, u32 *directory)
{
	struct fw_csr_iterator ci;
	int key, value;

	fw_csr_iterator_init(&ci, directory);
	while (fw_csr_iterator_next(&ci, &key, &value))
		if (key == SBP2_CSR_LOGICAL_UNIT_NUMBER &&
		    sbp2_add_logical_unit(tgt, value) < 0)
			return -ENOMEM;
	return 0;
}