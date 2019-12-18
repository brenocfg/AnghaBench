#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* context; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_11__ {TYPE_2__* config; TYPE_4__* private_data; } ;
typedef  TYPE_5__ hb_work_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  extradata_size; int /*<<< orphan*/ * extradata; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  bytes; } ;
struct TYPE_8__ {TYPE_1__ extradata; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Finalize(hb_work_object_t *w)
{
    hb_work_private_t *pv = w->private_data;

    // Then we need to recopy the header since it was modified
    if (pv->context->extradata != NULL)
    {
        memcpy(w->config->extradata.bytes, pv->context->extradata,
               pv->context->extradata_size);
        w->config->extradata.length = pv->context->extradata_size;
    }
}