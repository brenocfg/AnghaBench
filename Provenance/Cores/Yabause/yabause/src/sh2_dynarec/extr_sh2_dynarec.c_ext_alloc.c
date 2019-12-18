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
struct regstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rs1 ; 
 int /*<<< orphan*/ * rt1 ; 

void ext_alloc(struct regstat *current,int i)
{
  // Note: Don't need to actually alloc the source registers
  // FIXME: Constant propagation
  //alloc_reg(current,i,rs1[i]);
  alloc_reg(current,i,rt1[i]);
  clear_const(current,rs1[i]);
  clear_const(current,rt1[i]);
  dirty_reg(current,rt1[i]);
}