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
typedef  union U3 {int dummy; } U3 ;
typedef  int uint16_t ;
struct S1 {int dummy; } ;
typedef  long int8_t ;
typedef  long int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 struct S1* func_39 (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct S1*) ; 
 int /*<<< orphan*/  func_45 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct S1**** g_156 ; 
 long* g_285 ; 
 union U3 g_304 ; 
 int /*<<< orphan*/ ** g_54 ; 
 int /*<<< orphan*/  g_8 ; 
 int /*<<< orphan*/  safe_div_func_int8_t_s_s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_lshift_func_uint16_t_u_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static union U3  func_33(int8_t  p_34, int16_t  p_35, int32_t  p_36)
{ /* block id: 1 */
    int8_t l_44 = (-8L);
    int16_t *l_52 = (void*)0;
    int16_t *l_53 = &g_54[7][8];
    struct S1 *l_282 = (void*)0;
    struct S1 **l_287 = &g_156[2][1][7];
    struct S1 **l_288 = &l_282;
    int32_t l_289[5] = {1L,1L,1L,1L,1L};
    int32_t *l_290 = &g_285[0];
    int32_t *l_291 = (void*)0;
    int32_t *l_292 = &l_289[0];
    int32_t *l_293 = &l_289[3];
    int32_t *l_294 = (void*)0;
    int32_t *l_295 = &g_285[0];
    int32_t *l_296 = &g_285[0];
    int32_t *l_297 = &l_289[3];
    int32_t *l_298[1];
    int32_t l_299 = (-1L);
    int32_t l_300 = 0x460548ABL;
    uint16_t l_301 = 0x1E4AL;
    int i;
    for (i = 0; i < 1; i++)
        l_298[i] = (void*)0;
    (*l_288) = ((*l_287) = func_39(l_44, g_8, func_45((safe_lshift_func_uint16_t_u_s((safe_div_func_int8_t_s_s(p_35, 0x53L)), ((*l_53) = g_8))), g_8), l_282));
    l_301--;
    return g_304;
}