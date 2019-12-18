#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* p_hash_elem ;
struct TYPE_2__ {int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 unsigned int htab_hash_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
htab_hash_elem (const void *p)
{
  p_hash_elem elem = (p_hash_elem) p;
  return htab_hash_pointer (elem->insn);
}