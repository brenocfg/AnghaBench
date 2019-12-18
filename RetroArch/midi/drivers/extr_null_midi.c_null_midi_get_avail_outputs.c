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
union string_list_elem_attr {int /*<<< orphan*/  member_0; } ;
struct string_list {int dummy; } ;

/* Variables and functions */
 int string_list_append (struct string_list*,char*,union string_list_elem_attr) ; 

__attribute__((used)) static bool null_midi_get_avail_outputs(struct string_list *outputs)
{
   union string_list_elem_attr attr = {0};

   return string_list_append(outputs, "Null", attr);
}