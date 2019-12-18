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
struct neon_type_el {scalar_t__ type; int /*<<< orphan*/  size; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DDD ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQQ ; 
 scalar_t__ NT_unsigned ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_KEY ; 
 int N_SU_ALL ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_three_same (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_dyadic_i64_su (void)
{
  enum neon_shape rs = neon_select_shape (NS_DDD, NS_QQQ, NS_NULL);
  struct neon_type_el et = neon_check_type (3, rs,
    N_EQK, N_EQK, N_SU_ALL | N_KEY);
  neon_three_same (neon_quad (rs), et.type == NT_unsigned, et.size);
}