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
struct neon_type_el {int /*<<< orphan*/  size; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DD ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQ ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_I16 ; 
 int N_I32 ; 
 int N_I8 ; 
 int N_KEY ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_two_same (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_clz (void)
{
  enum neon_shape rs = neon_select_shape (NS_DD, NS_QQ, NS_NULL);
  struct neon_type_el et = neon_check_type (2, rs,
    N_EQK, N_I8 | N_I16 | N_I32 | N_KEY);
  neon_two_same (neon_quad (rs), 1, et.size);
}