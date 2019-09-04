#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  field_picture; int /*<<< orphan*/  mb_type; int /*<<< orphan*/ * ref_index; int /*<<< orphan*/ * motion_val; int /*<<< orphan*/ * tf; int /*<<< orphan*/ * f; } ;
struct TYPE_6__ {int /*<<< orphan*/  field_picture; int /*<<< orphan*/  mb_type; int /*<<< orphan*/ * ref_index; int /*<<< orphan*/ * motion_val; int /*<<< orphan*/  tf; int /*<<< orphan*/ * f; } ;
typedef  TYPE_1__ Picture ;
typedef  TYPE_2__ ERPicture ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_erpic(ERPicture *dst, Picture *src)
{
    int i;

    memset(dst, 0, sizeof(*dst));
    if (!src) {
        dst->f  = NULL;
        dst->tf = NULL;
        return;
    }

    dst->f = src->f;
    dst->tf = &src->tf;

    for (i = 0; i < 2; i++) {
        dst->motion_val[i] = src->motion_val[i];
        dst->ref_index[i] = src->ref_index[i];
    }

    dst->mb_type = src->mb_type;
    dst->field_picture = src->field_picture;
}