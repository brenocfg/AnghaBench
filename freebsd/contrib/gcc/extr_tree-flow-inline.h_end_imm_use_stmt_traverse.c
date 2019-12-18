#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  iter_node; } ;
typedef  TYPE_1__ imm_use_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  delink_imm_use (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
end_imm_use_stmt_traverse (imm_use_iterator *imm)
{
  delink_imm_use (&(imm->iter_node));
}