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
typedef  size_t uint16_t ;
struct beiscsi_hba {int /*<<< orphan*/ ** conn_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 size_t BE_GET_CRI_FROM_CID (unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int beiscsi_unbind_conn_to_cid(struct beiscsi_hba *phba,
				      unsigned int cid)
{
	uint16_t cri_index = BE_GET_CRI_FROM_CID(cid);

	if (phba->conn_table[cri_index])
		phba->conn_table[cri_index] = NULL;
	else {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : Connection table Not occupied.\n");
		return -EINVAL;
	}
	return 0;
}