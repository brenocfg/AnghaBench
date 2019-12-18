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
struct tagged_tu_seen_cache {struct tagged_tu_seen_cache* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tagged_tu_seen_cache*) ; 
 struct tagged_tu_seen_cache const* tagged_tu_seen_base ; 

__attribute__((used)) static void
free_all_tagged_tu_seen_up_to (const struct tagged_tu_seen_cache *tu_til)
{
  const struct tagged_tu_seen_cache *tu = tagged_tu_seen_base;
  while (tu != tu_til)
    {
      struct tagged_tu_seen_cache *tu1 = (struct tagged_tu_seen_cache*)tu;
      tu = tu1->next;
      free (tu1);
    }
  tagged_tu_seen_base = tu_til;
}