#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ h; scalar_t__ w; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {TYPE_1__ rect; } ;
struct TYPE_8__ {int /*<<< orphan*/  asset; TYPE_2__ window; } ;
typedef  TYPE_3__ itemDef_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* drawHandlePic ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_5__* DC ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void Item_Image_Paint(itemDef_t *item) {
	if (item == NULL) {
		return;
	}
	DC->drawHandlePic(item->window.rect.x+1, item->window.rect.y+1, item->window.rect.w-2, item->window.rect.h-2, item->asset);
}