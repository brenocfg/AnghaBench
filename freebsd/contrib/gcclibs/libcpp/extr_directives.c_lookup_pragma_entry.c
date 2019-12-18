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
struct pragma_entry {struct pragma_entry* next; int /*<<< orphan*/  const* pragma; } ;
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */

__attribute__((used)) static struct pragma_entry *
lookup_pragma_entry (struct pragma_entry *chain, const cpp_hashnode *pragma)
{
  while (chain && chain->pragma != pragma)
    chain = chain->next;

  return chain;
}