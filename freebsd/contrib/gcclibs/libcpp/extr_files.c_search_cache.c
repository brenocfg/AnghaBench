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
struct file_hash_entry {struct file_hash_entry* next; int /*<<< orphan*/  const* start_dir; } ;
typedef  int /*<<< orphan*/  cpp_dir ;

/* Variables and functions */

__attribute__((used)) static struct file_hash_entry *
search_cache (struct file_hash_entry *head, const cpp_dir *start_dir)
{
  while (head && head->start_dir != start_dir)
    head = head->next;

  return head;
}