#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 TYPE_1__* hb_preset_index_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

hb_preset_index_t* hb_preset_index_dup(const hb_preset_index_t *path)
{
    if (path == NULL)
        return NULL;
    return hb_preset_index_init(path->index, path->depth);
}