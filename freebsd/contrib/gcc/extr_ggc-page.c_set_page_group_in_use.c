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
struct TYPE_3__ {int in_use; int /*<<< orphan*/  allocation; } ;
typedef  TYPE_1__ page_group ;

/* Variables and functions */
 int page_group_index (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void
set_page_group_in_use (page_group *group, char *page)
{
  group->in_use |= 1 << page_group_index (group->allocation, page);
}