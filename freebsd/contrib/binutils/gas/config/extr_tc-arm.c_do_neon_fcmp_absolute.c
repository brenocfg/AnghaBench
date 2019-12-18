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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DDD ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQQ ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_F32 ; 
 int N_KEY ; 
 int /*<<< orphan*/  neon_check_type (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_three_same (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
do_neon_fcmp_absolute (void)
{
  enum neon_shape rs = neon_select_shape (NS_DDD, NS_QQQ, NS_NULL);
  neon_check_type (3, rs, N_EQK, N_EQK, N_F32 | N_KEY);
  /* Size field comes from bit mask.  */
  neon_three_same (neon_quad (rs), 1, -1);
}