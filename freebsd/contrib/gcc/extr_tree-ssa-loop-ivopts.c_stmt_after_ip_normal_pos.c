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
typedef  scalar_t__ tree ;
struct loop {scalar_t__ latch; } ;
typedef  scalar_t__ basic_block ;

/* Variables and functions */
 scalar_t__ bb_for_stmt (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ ip_normal_pos (struct loop*) ; 
 scalar_t__ last_stmt (scalar_t__) ; 

__attribute__((used)) static bool
stmt_after_ip_normal_pos (struct loop *loop, tree stmt)
{
  basic_block bb = ip_normal_pos (loop), sbb = bb_for_stmt (stmt);

  gcc_assert (bb);

  if (sbb == loop->latch)
    return true;

  if (sbb != bb)
    return false;

  return stmt == last_stmt (bb);
}