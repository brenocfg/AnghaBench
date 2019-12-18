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
struct web_entry {struct web_entry* pred; } ;

/* Variables and functions */

struct web_entry *
unionfind_root (struct web_entry *element)
{
  struct web_entry *element1 = element, *element2;

  while (element->pred)
    element = element->pred;
  while (element1->pred)
    {
      element2 = element1->pred;
      element1->pred = element;
      element1 = element2;
    }
  return element;
}