#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ page_count; } ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 TYPE_1__ memory_page_dictionary ; 

__attribute__((used)) static void
retire_memory_page_dictionary (void)
{
  memory_page_dictionary.page_count = (LONGEST) - 1;
}