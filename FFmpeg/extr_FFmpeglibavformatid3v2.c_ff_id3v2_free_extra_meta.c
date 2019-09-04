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
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  data; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ ID3v2ExtraMeta ;
typedef  TYPE_2__ ID3v2EMFunc ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_2__* get_extra_meta_func (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ff_id3v2_free_extra_meta(ID3v2ExtraMeta **extra_meta)
{
    ID3v2ExtraMeta *current = *extra_meta, *next;
    const ID3v2EMFunc *extra_func;

    while (current) {
        if ((extra_func = get_extra_meta_func(current->tag, 1)))
            extra_func->free(current->data);
        next = current->next;
        av_freep(&current);
        current = next;
    }

    *extra_meta = NULL;
}