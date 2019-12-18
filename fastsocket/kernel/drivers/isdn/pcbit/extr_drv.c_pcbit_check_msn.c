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
struct pcbit_dev {struct msn_entry* msn_list; } ;
struct msn_entry {int /*<<< orphan*/ * msn; struct msn_entry* next; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int pcbit_check_msn(struct pcbit_dev *dev, char *msn)
{
	struct msn_entry *ptr;
	
	for (ptr=dev->msn_list; ptr; ptr=ptr->next) {

		if (ptr->msn == NULL) 
			return 1;
		
		if (strcmp(ptr->msn, msn) == 0)
			return 1;
	}

	return 0;
}