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
typedef  int /*<<< orphan*/ * used_part_t ;
struct used_part_map {unsigned int uid; int /*<<< orphan*/ * to; } ;

/* Variables and functions */
 scalar_t__ htab_find_with_hash (int /*<<< orphan*/ ,struct used_part_map*,unsigned int) ; 
 int /*<<< orphan*/  used_portions ; 

__attribute__((used)) static used_part_t
up_lookup (unsigned int uid)
{
  struct used_part_map *h, in;
  in.uid = uid;
  h = (struct used_part_map *) htab_find_with_hash (used_portions, &in, uid);
  if (!h)
    return NULL;
  return h->to;
}