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
struct neon_type_el {scalar_t__ type; int /*<<< orphan*/  size; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_2__ {int instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DD ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQ ; 
 scalar_t__ NT_unsigned ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_KEY ; 
 int N_SU_32 ; 
 TYPE_1__ inst ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_two_same (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_pair_long (void)
{
  enum neon_shape rs = neon_select_shape (NS_DD, NS_QQ, NS_NULL);
  struct neon_type_el et = neon_check_type (2, rs, N_EQK, N_SU_32 | N_KEY);
  /* Unsigned is encoded in OP field (bit 7) for these instruction.  */
  inst.instruction |= (et.type == NT_unsigned) << 7;
  neon_two_same (neon_quad (rs), 1, et.size);
}