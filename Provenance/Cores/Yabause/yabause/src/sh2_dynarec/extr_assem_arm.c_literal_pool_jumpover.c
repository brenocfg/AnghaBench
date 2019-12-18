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

/* Variables and functions */
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  literal_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  literalcount ; 
 int** literals ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  set_jump_target (int,int) ; 

void literal_pool_jumpover(int n)
{
  if(!literalcount) return;
  if(n) {
    if((int)out-literals[0][0]<4096-n) return;
  }
  int jaddr=(int)out;
  emit_jmp(0);
  literal_pool(0);
  set_jump_target(jaddr,(int)out);
}