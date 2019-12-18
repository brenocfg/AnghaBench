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

/* Variables and functions */
 int /*<<< orphan*/  OPENETH_MODER_REG ; 
 int /*<<< orphan*/  OPENETH_RST ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void openeth_reset(void)
{
    REG_SET_BIT(OPENETH_MODER_REG, OPENETH_RST);
    REG_CLR_BIT(OPENETH_MODER_REG, OPENETH_RST);
}