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
struct ehl_map_entry {scalar_t__ label; } ;

/* Variables and functions */

__attribute__((used)) static int
ehl_eq (const void *pentry, const void *pdata)
{
  struct ehl_map_entry *entry = (struct ehl_map_entry *) pentry;
  struct ehl_map_entry *data = (struct ehl_map_entry *) pdata;

  return entry->label == data->label;
}