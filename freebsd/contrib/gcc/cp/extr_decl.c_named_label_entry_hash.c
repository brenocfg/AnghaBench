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
struct named_label_entry {int /*<<< orphan*/  label_decl; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
named_label_entry_hash (const void *data)
{
  const struct named_label_entry *ent = (const struct named_label_entry *) data;
  return DECL_UID (ent->label_decl);
}