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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ LABEL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_PRESERVE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forced_labels ; 
 int /*<<< orphan*/  in_expr_list_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
can_delete_label_p (rtx label)
{
  return (!LABEL_PRESERVE_P (label)
	  /* User declared labels must be preserved.  */
	  && LABEL_NAME (label) == 0
	  && !in_expr_list_p (forced_labels, label));
}