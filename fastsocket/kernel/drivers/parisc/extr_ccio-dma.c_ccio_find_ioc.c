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
struct ioc {int hw_path; struct ioc* next; } ;

/* Variables and functions */
 int ioc_count ; 
 struct ioc* ioc_list ; 

__attribute__((used)) static struct ioc * ccio_find_ioc(int hw_path)
{
	int i;
	struct ioc *ioc;

	ioc = ioc_list;
	for (i = 0; i < ioc_count; i++) {
		if (ioc->hw_path == hw_path)
			return ioc;

		ioc = ioc->next;
	}

	return NULL;
}