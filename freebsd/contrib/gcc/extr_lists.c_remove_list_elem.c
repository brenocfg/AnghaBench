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
 int /*<<< orphan*/ * find_list_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_list_node (int /*<<< orphan*/ *) ; 

rtx
remove_list_elem (rtx elem, rtx *listp)
{
  rtx node;

  listp = find_list_elem (elem, listp);
  node = *listp;
  remove_list_node (listp);
  return node;
}