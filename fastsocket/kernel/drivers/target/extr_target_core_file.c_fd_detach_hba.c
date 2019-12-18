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
struct se_hba {struct fd_host* hba_ptr; int /*<<< orphan*/  hba_id; } ;
struct fd_host {int /*<<< orphan*/  fd_host_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fd_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fd_detach_hba(struct se_hba *hba)
{
	struct fd_host *fd_host = hba->hba_ptr;

	pr_debug("CORE_HBA[%d] - Detached FILEIO HBA: %u from Generic"
		" Target Core\n", hba->hba_id, fd_host->fd_host_id);

	kfree(fd_host);
	hba->hba_ptr = NULL;
}