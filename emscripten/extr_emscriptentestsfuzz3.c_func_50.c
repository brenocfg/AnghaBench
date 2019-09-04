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
typedef  union U2 {int dummy; } U2 ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  f3; } ;

/* Variables and functions */
 TYPE_1__ g_42 ; 
 int /*<<< orphan*/ * g_60 ; 
 int safe_sub_func_uint8_t_u_u (int,int) ; 

__attribute__((used)) static uint16_t  func_50(int32_t * p_51, uint16_t  p_52, int8_t  p_53, int32_t * p_54, union U2  p_55)
{ /* block id: 8 */
    for (p_53 = 0; (p_53 < (-11)); p_53 = safe_sub_func_uint8_t_u_u(p_53, 9))
    { /* block id: 11 */
        int32_t **l_67 = (void*)0;
        int32_t **l_68 = &g_60;
        (*l_68) = p_54;
    }
    return g_42.f3;
}