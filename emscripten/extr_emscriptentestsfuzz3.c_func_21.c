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
union U0 {long member_0; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_25 ; 

__attribute__((used)) static union U0  func_21(uint32_t  p_22)
{ /* block id: 1 */
    int32_t *l_24 = &g_25;
    union U0 l_26 = {-3L};
    (*l_24) = p_22;
    return l_26;
}