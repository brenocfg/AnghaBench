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
typedef  scalar_t__ uint16_t ;
struct S0 {int f1; int f0; scalar_t__ const f3; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f4; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_60 (int /*<<< orphan*/ ) ; 
 scalar_t__ g_12 ; 
 int /*<<< orphan*/  g_20 ; 
 int /*<<< orphan*/ * g_53 ; 
 int /*<<< orphan*/ * g_54 ; 
 int /*<<< orphan*/ * g_6 ; 
 TYPE_1__*** g_92 ; 
 scalar_t__ const safe_lshift_func_int8_t_s_s (int,int /*<<< orphan*/ ) ; 
 int safe_lshift_func_uint16_t_u_s (int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  safe_mod_func_int8_t_s_s (int,unsigned long) ; 
 int /*<<< orphan*/  safe_mul_func_int8_t_s_s (int /*<<< orphan*/ ,int) ; 
 scalar_t__ safe_sub_func_int8_t_s_s (int,scalar_t__ const) ; 

__attribute__((used)) static int32_t * func_49(int32_t ** p_50, int16_t  p_51, struct S0  p_52)
{ /* block id: 24 */
    const uint16_t l_110 = 0xE3F5L;
    int32_t *l_111 = &g_92[3][1][3].f4;
    (*l_111) = (safe_mul_func_int8_t_s_s(func_40((**p_50)), ((safe_sub_func_int8_t_s_s((((func_60((*g_54)) , (*g_53)) != (g_20 , (*p_50))) & (safe_lshift_func_uint16_t_u_s((safe_mod_func_int8_t_s_s(((p_52.f1 = p_52.f0) & (((safe_lshift_func_int8_t_s_s((p_52.f3 == l_110), g_6[8])) > l_110) , g_92[3][1][3].f1)), 1UL)), l_110))), l_110)) > g_12)));
    return l_111;
}