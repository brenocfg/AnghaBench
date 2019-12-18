#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int EHWPOISON ; 
 int FOLL_HWPOISON ; 
 int FOLL_TOUCH ; 
 int FOLL_WRITE ; 
 int __get_user_pages (TYPE_1__*,int /*<<< orphan*/ ,unsigned long,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 

__attribute__((used)) static inline int check_user_page_hwpoison(unsigned long addr)
{
	int rc, flags = FOLL_TOUCH | FOLL_HWPOISON | FOLL_WRITE;

	rc = __get_user_pages(current, current->mm, addr, 1,
			      flags, NULL, NULL);
	return rc == -EHWPOISON;
}