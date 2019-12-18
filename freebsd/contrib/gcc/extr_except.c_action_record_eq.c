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
struct action_record {scalar_t__ filter; scalar_t__ next; } ;

/* Variables and functions */

__attribute__((used)) static int
action_record_eq (const void *pentry, const void *pdata)
{
  const struct action_record *entry = (const struct action_record *) pentry;
  const struct action_record *data = (const struct action_record *) pdata;
  return entry->filter == data->filter && entry->next == data->next;
}