#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_tim ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hostap_set_tim(local_info_t *local, int aid, int set)
{
	if (local->func->set_tim)
		local->func->set_tim(local->dev, aid, set);
}