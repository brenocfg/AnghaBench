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
struct cref_hash_entry {int /*<<< orphan*/  demangled; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cref_sort_array (const void *a1, const void *a2)
{
  const struct cref_hash_entry * const *p1 = a1;
  const struct cref_hash_entry * const *p2 = a2;

  return strcmp ((*p1)->demangled, (*p2)->demangled);
}