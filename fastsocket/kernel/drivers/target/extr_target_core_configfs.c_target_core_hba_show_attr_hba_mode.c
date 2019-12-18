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
struct se_hba {int hba_flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HBA_FLAGS_PSCSI_MODE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t target_core_hba_show_attr_hba_mode(struct se_hba *hba,
				char *page)
{
	int hba_mode = 0;

	if (hba->hba_flags & HBA_FLAGS_PSCSI_MODE)
		hba_mode = 1;

	return sprintf(page, "%d\n", hba_mode);
}