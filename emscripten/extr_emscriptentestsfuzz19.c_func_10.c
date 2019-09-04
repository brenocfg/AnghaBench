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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned long uint32_t ;
typedef  unsigned long int8_t ;
typedef  long int32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int g_1298 ; 
 int /*<<< orphan*/ * g_143 ; 
 int g_290 ; 
 long* g_297 ; 
 int /*<<< orphan*/  g_43 ; 
 int /*<<< orphan*/ *** g_905 ; 
 int safe_add_func_uint16_t_u_u (int,int) ; 
 int /*<<< orphan*/  safe_mod_func_int32_t_s_s (long,unsigned long) ; 

__attribute__((used)) static int8_t  func_10(uint32_t  p_11)
{ /* block id: 756 */
    uint32_t l_1605 = 3UL;
    uint8_t **l_1608[3][5] = {{&g_43,&g_43,&g_43,&g_43,&g_43},{&g_43,&g_43,&g_43,&g_43,&g_43},{&g_43,&g_43,&g_43,&g_43,&g_43}};
    int i, j;
    for (g_290 = 0; (g_290 >= 1); g_290++)
    { /* block id: 759 */
        int32_t l_1603 = (-1L);
        int32_t *l_1604[10];
        int i;
        for (i = 0; i < 10; i++)
            l_1604[i] = &g_297[1];
        (*g_143) = (safe_mod_func_int32_t_s_s(l_1603, p_11));
        l_1605++;
        if (p_11)
            break;
    }
    (*g_905) = l_1608[2][0];
    for (g_1298 = (-1); (g_1298 == 37); g_1298 = safe_add_func_uint16_t_u_u(g_1298, 9))
    { /* block id: 767 */
        return l_1605;
    }
    return l_1605;
}