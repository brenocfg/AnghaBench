#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UI_tMenuItem ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 TYPE_1__* FindMenuItem (int /*<<< orphan*/ *,int) ; 
 int UI_ITEM_CHECK ; 
 int UI_ITEM_CHECKED ; 

__attribute__((used)) static void SetItemChecked(UI_tMenuItem *mip, int option, int checked)
{
	FindMenuItem(mip, option)->flags = checked ? (UI_ITEM_CHECK | UI_ITEM_CHECKED) : UI_ITEM_CHECK;
}