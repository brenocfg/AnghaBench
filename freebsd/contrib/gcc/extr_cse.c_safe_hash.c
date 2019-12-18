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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int hash_rtx (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline unsigned
safe_hash (rtx x, enum machine_mode mode)
{
  int dummy_do_not_record;
  return hash_rtx (x, mode, &dummy_do_not_record, NULL, true);
}