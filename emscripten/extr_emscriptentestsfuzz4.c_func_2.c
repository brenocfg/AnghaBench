#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
struct TYPE_6__ {unsigned long member_0; unsigned long member_1; unsigned long member_2; unsigned long member_3; } ;
struct TYPE_5__ {int member_0; unsigned long member_1; int member_2; unsigned long member_3; } ;
struct TYPE_4__ {int member_0; unsigned long member_1; unsigned long member_2; int member_3; } ;

/* Variables and functions */
 int g_11 ; 
 int* g_13 ; 
 int** g_6 ; 
 int safe_add_func_uint32_t_u_u (int,int) ; 

__attribute__((used)) static int32_t  func_2(int8_t * p_3)
{ /* block id: 1 */
    uint32_t l_15[4][3][4] = {{{0x1943EC3EL,8UL,1UL,0x58E7EA1BL},{0x1943EC3EL,2UL,0x58E7EA1BL,4294967292UL},{0UL,1UL,0UL,4294967293UL}},{{0x4898D08FL,1UL,0x4898D08FL,4294967292UL},{0UL,0x1943EC3EL,4294967292UL,0x4898D08FL},{2UL,4294967293UL,4294967292UL,0UL}},{{0UL,0x1943EC3EL,8UL,0x1943EC3EL},{4294967292UL,0x58E7EA1BL,0x1943EC3EL,0x1943EC3EL},{0x1943EC3EL,0x58E7EA1BL,0x4898D08FL,2UL}},{{1UL,0UL,8UL,8UL},{0x4898D08FL,1UL,8UL,0UL},{0x58E7EA1BL,4294967292UL,0x58E7EA1BL,0x1943EC3EL}}};
    int i, j, k;
    for (g_6[2][7] = (-24); (g_6[2][7] >= (-7)); g_6[2][7] = safe_add_func_uint32_t_u_u(g_6[2][7], 1))
    { /* block id: 4 */
        int32_t *l_9 = (void*)0;
        int32_t *l_10 = &g_11;
        (*l_10) &= 0x1B35D569L;
        for (g_11 = 0; (g_11 <= 7); g_11 += 1)
        { /* block id: 8 */
            int32_t **l_12[6] = {&l_10,&l_10,&l_10,&l_10,&l_10,&l_10};
            int i;
            g_13 = l_9;
            l_15[1][2][0]--;
        }
    }
    return l_15[0][1][1];
}