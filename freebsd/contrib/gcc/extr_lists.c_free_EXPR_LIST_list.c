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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  free_list (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unused_expr_list ; 

void
free_EXPR_LIST_list (rtx *listp)
{
  if (*listp == 0)
    return;
  free_list (listp, &unused_expr_list);
}