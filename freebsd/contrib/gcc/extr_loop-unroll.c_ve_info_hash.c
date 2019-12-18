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
struct var_to_expand {int /*<<< orphan*/  insn; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_UID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
ve_info_hash (const void *ves)
{
  return (hashval_t) INSN_UID (((struct var_to_expand *) ves)->insn);
}