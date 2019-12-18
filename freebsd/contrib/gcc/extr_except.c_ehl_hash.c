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
struct ehl_map_entry {int /*<<< orphan*/  label; } ;
typedef  int const hashval_t ;

/* Variables and functions */
 int const CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
ehl_hash (const void *pentry)
{
  struct ehl_map_entry *entry = (struct ehl_map_entry *) pentry;

  /* 2^32 * ((sqrt(5) - 1) / 2) */
  const hashval_t scaled_golden_ratio = 0x9e3779b9;
  return CODE_LABEL_NUMBER (entry->label) * scaled_golden_ratio;
}