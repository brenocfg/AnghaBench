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
typedef  union U4 {int dummy; } U4 ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f0; } ;
struct TYPE_6__ {TYPE_1__ f3; } ;
struct TYPE_5__ {int /*<<< orphan*/  f3; } ;

/* Variables and functions */
 TYPE_3__ g_38 ; 
 TYPE_2__ g_53 ; 
 int /*<<< orphan*/ ** g_58 ; 
 int /*<<< orphan*/  g_60 ; 
 int /*<<< orphan*/  safe_rshift_func_uint8_t_u_s (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const int8_t * func_45(int8_t * p_46, int32_t  p_47, uint32_t  p_48, union U4  p_49, int8_t  p_50)
{ /* block id: 2 */
    int32_t *l_57 = &g_53.f3;
    int32_t *l_59 = &g_60;
    const int8_t *l_61 = &g_38.f3.f0;
    g_58[2][2] ^= ((*l_57) = (safe_rshift_func_uint8_t_u_s(g_38.f3.f3, 2)));
    (*l_59) ^= (*l_57);
    return l_61;
}