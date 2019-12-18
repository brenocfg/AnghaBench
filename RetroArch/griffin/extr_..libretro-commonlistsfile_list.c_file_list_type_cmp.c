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
struct item_file {scalar_t__ type; } ;

/* Variables and functions */

__attribute__((used)) static int file_list_type_cmp(const void *a_, const void *b_)
{
   const struct item_file *a = (const struct item_file*)a_;
   const struct item_file *b = (const struct item_file*)b_;
   if (a->type < b->type)
      return -1;
   if (a->type == b->type)
      return 0;

   return 1;
}