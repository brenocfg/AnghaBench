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
struct action_record {int next; scalar_t__ filter; } ;
typedef  scalar_t__ hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
action_record_hash (const void *pentry)
{
  const struct action_record *entry = (const struct action_record *) pentry;
  return entry->next * 1009 + entry->filter;
}