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
struct pred_data {char const* name; } ;

/* Variables and functions */
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct pred_data*) ; 
 int /*<<< orphan*/  predicate_table ; 

struct pred_data *
lookup_predicate (const char *name)
{
  struct pred_data key;
  key.name = name;
  return (struct pred_data *) htab_find (predicate_table, &key);
}