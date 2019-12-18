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
struct string_list {char const* name; struct string_list* next; } ;

/* Variables and functions */
 struct string_list* xmalloc (int) ; 

__attribute__((used)) static struct string_list *
string_list_cons (const char *string, struct string_list *rest)
{
  struct string_list *temp = xmalloc (sizeof (struct string_list));

  temp->next = rest;
  temp->name = string;
  return temp;
}