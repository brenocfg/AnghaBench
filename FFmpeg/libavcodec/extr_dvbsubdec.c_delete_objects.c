#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* object_list; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ DVBSubObject ;
typedef  TYPE_2__ DVBSubContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

__attribute__((used)) static void delete_objects(DVBSubContext *ctx)
{
    while (ctx->object_list) {
        DVBSubObject *object = ctx->object_list;

        ctx->object_list = object->next;

        av_freep(&object);
    }
}