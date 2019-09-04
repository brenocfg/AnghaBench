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
struct ucred {int dummy; } ;
struct fileglob {int /*<<< orphan*/  fg_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct ucred*,struct fileglob*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  file_check_mmap_downgrade ; 

void
mac_file_check_mmap_downgrade(struct ucred *cred, struct fileglob *fg,
    int *prot)
{
	int result = *prot;

	MAC_PERFORM(file_check_mmap_downgrade, cred, fg, fg->fg_label,
	    &result);

	*prot = result;
}