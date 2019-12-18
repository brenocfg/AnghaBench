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
struct neon_type_el {unsigned int size; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_2__ {int instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DD ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQ ; 
 int N_16 ; 
 int N_32 ; 
 int N_8 ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_KEY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_two_same (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void
do_neon_rev (void)
{
  enum neon_shape rs = neon_select_shape (NS_DD, NS_QQ, NS_NULL);
  struct neon_type_el et = neon_check_type (2, rs,
    N_EQK, N_8 | N_16 | N_32 | N_KEY);
  unsigned op = (inst.instruction >> 7) & 3;
  /* N (width of reversed regions) is encoded as part of the bitmask. We
     extract it here to check the elements to be reversed are smaller.
     Otherwise we'd get a reserved instruction.  */
  unsigned elsize = (op == 2) ? 16 : (op == 1) ? 32 : (op == 0) ? 64 : 0;
  assert (elsize != 0);
  constraint (et.size >= elsize,
              _("elements must be smaller than reversal region"));
  neon_two_same (neon_quad (rs), 1, et.size);
}