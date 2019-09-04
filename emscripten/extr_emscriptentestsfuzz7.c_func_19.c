#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union U2 {long member_0; } ;
union U1 {int member_0; } ;
union U0 {unsigned long member_0; } ;
typedef  int int8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_23 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,union U0,scalar_t__*) ; 
 int /*<<< orphan*/  func_29 (scalar_t__**,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  func_36 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_38 (int /*<<< orphan*/ ,int,union U2,union U0) ; 
 scalar_t__ func_45 (scalar_t__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  func_55 (scalar_t__,union U1,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  func_61 (int,scalar_t__**) ; 
 scalar_t__ g_11 ; 
 scalar_t__ g_1124 ; 
 scalar_t__* g_16 ; 
 int /*<<< orphan*/  g_468 ; 
 int /*<<< orphan*/ * g_537 ; 
 int /*<<< orphan*/ *** g_586 ; 
 int* g_76 ; 
 int /*<<< orphan*/  g_77 ; 
 int /*<<< orphan*/ * g_82 ; 
 int /*<<< orphan*/  g_894 ; 
 TYPE_1__* g_9 ; 
 int /*<<< orphan*/  safe_lshift_func_int8_t_s_s (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_mod_func_uint32_t_u_u (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_mod_func_uint8_t_u_u (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_mul_func_int16_t_s_s (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t  func_19(int32_t  p_20)
{ /* block id: 7 */
    int32_t *l_35 = &g_11;
    int32_t **l_34 = &l_35;
    union U1 l_60 = {0xAD4F6C55L};
    int8_t *l_84 = &g_76[2];
    union U2 l_85 = {-1L};
    union U0 l_86 = {4294967295UL};
    int32_t *l_1453 = &g_1124;
    (*l_1453) |= ((safe_mod_func_uint8_t_u_u((func_23(func_29(l_34, (p_20 , func_36(func_38(g_9[0].f0, ((*l_84) = ((safe_mul_func_int16_t_s_s((((**l_34) && func_45(p_20, (safe_mod_func_uint32_t_u_u(((safe_lshift_func_int8_t_s_s(0xC8L, (func_55(p_20, l_60, func_61((((*g_16) && 0x04518073L) > 0x36L), &g_16), g_11) , (-1L)))) , p_20), g_9[0].f0)), g_9[3], g_82, p_20)) , (**l_34)), g_77)) || (**l_34))), l_85, l_86))), &g_468, p_20), p_20, p_20, l_86, (*l_34)) , 249UL), g_894)) > p_20);
    (*l_35) = p_20;
    (*g_537) = ((***g_586) , (*g_82));
    return (*g_16);
}