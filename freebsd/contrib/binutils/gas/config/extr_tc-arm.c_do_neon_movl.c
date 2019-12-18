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
struct neon_type_el {int size; scalar_t__ type; } ;
struct TYPE_2__ {unsigned int instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_QD ; 
 scalar_t__ NT_unsigned ; 
 int N_DBL ; 
 int N_EQK ; 
 int N_KEY ; 
 int N_SU_32 ; 
 TYPE_1__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  neon_two_same (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
do_neon_movl (void)
{
  struct neon_type_el et = neon_check_type (2, NS_QD,
    N_EQK | N_DBL, N_SU_32 | N_KEY);
  unsigned sizebits = et.size >> 3;
  inst.instruction |= sizebits << 19;
  neon_two_same (0, et.type == NT_unsigned, -1);
}