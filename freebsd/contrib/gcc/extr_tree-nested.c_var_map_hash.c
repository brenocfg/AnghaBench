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
struct var_map_elt {int /*<<< orphan*/  old; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
var_map_hash (const void *x)
{
  const struct var_map_elt *a = (const struct var_map_elt *) x;
  return htab_hash_pointer (a->old);
}