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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct S1 {unsigned long member_0; unsigned long member_1; } ;
struct S0 {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_84 ; 
 int /*<<< orphan*/  safe_lshift_func_uint16_t_u_u (int,int) ; 

__attribute__((used)) static struct S1  func_8(uint32_t  p_9, struct S0  p_10)
{ /* block id: 574 */
    uint16_t l_1072 = 0xD8F4L;
    int32_t *l_1073 = &g_84;
    struct S1 l_1074 = {1UL,1UL};
    (*l_1073) = (safe_lshift_func_uint16_t_u_u(l_1072, 8));
    return l_1074;
}