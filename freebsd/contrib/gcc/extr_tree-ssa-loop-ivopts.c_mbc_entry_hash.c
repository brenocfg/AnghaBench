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
struct mbc_entry {int cst; scalar_t__ mode; } ;
typedef  int hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
mbc_entry_hash (const void *entry)
{
  const struct mbc_entry *e = entry;

  return 57 * (hashval_t) e->mode + (hashval_t) (e->cst % 877);
}