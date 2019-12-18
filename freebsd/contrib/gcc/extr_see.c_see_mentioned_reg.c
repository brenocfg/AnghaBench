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
struct see_mentioned_reg_data {int mentioned; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
see_mentioned_reg (rtx *x, void *data)
{
  struct see_mentioned_reg_data *d
    = (struct see_mentioned_reg_data *) data;

  if (reg_mentioned_p (d->reg, *x))
    d->mentioned = true;
}