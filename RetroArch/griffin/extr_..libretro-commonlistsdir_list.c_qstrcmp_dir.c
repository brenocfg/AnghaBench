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
struct TYPE_2__ {int i; } ;
struct string_list_elem {int /*<<< orphan*/  data; TYPE_1__ attr; } ;

/* Variables and functions */
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qstrcmp_dir(const void *a_, const void *b_)
{
   const struct string_list_elem *a = (const struct string_list_elem*)a_;
   const struct string_list_elem *b = (const struct string_list_elem*)b_;
   int a_type = a->attr.i;
   int b_type = b->attr.i;

   /* Sort directories before files. */
   if (a_type != b_type)
      return b_type - a_type;
   return strcasecmp(a->data, b->data);
}