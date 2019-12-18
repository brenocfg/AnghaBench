#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* buf_t ;
struct TYPE_4__ {int b_validend; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_EOT ; 

__attribute__((used)) static void
cluster_EOT(buf_t cbp_head, buf_t cbp_tail, int zero_offset)
{
        cbp_head->b_validend = zero_offset;
        cbp_tail->b_flags |= B_EOT;
}