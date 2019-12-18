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
struct value_data {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_value (int /*<<< orphan*/ ,struct value_data*) ; 

__attribute__((used)) static void
kill_clobbered_value (rtx x, rtx set, void *data)
{
  struct value_data *vd = data;
  if (GET_CODE (set) == CLOBBER)
    kill_value (x, vd);
}