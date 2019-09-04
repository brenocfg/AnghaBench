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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int8_t ;
typedef  int int32_t ;
struct TYPE_2__ {int f1; } ;

/* Variables and functions */
 int g_500 ; 
 TYPE_1__ g_82 ; 

__attribute__((used)) static uint32_t  func_41(int32_t  p_42, uint16_t * p_43, int32_t  p_44, uint16_t  p_45, int8_t * p_46)
{ /* block id: 359 */
    int32_t l_580 = 4L;
    for (g_82.f1 = (-1); (g_82.f1 < 7); g_82.f1++)
    { /* block id: 362 */
        int8_t l_578 = 0x96L;
        int32_t *l_579 = &g_500;
        (*l_579) = l_578;
        l_580 &= (~p_42);
    }
    return l_580;
}