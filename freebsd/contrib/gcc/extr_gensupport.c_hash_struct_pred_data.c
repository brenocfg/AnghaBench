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
struct pred_data {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_hash_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
hash_struct_pred_data (const void *ptr)
{
  return htab_hash_string (((const struct pred_data *)ptr)->name);
}