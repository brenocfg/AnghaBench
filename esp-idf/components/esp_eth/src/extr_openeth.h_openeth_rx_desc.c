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
typedef  int /*<<< orphan*/  openeth_rx_desc_t ;

/* Variables and functions */
 scalar_t__ OPENETH_DESC_BASE ; 
 int OPENETH_DESC_CNT ; 
 int TX_BUF_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline openeth_rx_desc_t* openeth_rx_desc(int idx)
{
    assert(idx < OPENETH_DESC_CNT - TX_BUF_COUNT);
    return &((openeth_rx_desc_t*)OPENETH_DESC_BASE)[idx + TX_BUF_COUNT];
}