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
struct TYPE_3__ {scalar_t__ imm_use; scalar_t__ end_p; } ;
typedef  TYPE_1__ imm_use_iterator ;

/* Variables and functions */

__attribute__((used)) static inline bool
end_imm_use_stmt_p (imm_use_iterator *imm)
{
  return (imm->imm_use == imm->end_p);
}