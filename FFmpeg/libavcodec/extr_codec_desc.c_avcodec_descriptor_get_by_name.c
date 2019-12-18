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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVCodecDescriptor ;

/* Variables and functions */
 TYPE_1__* avcodec_descriptor_next (TYPE_1__ const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const AVCodecDescriptor *avcodec_descriptor_get_by_name(const char *name)
{
    const AVCodecDescriptor *desc = NULL;

    while ((desc = avcodec_descriptor_next(desc)))
        if (!strcmp(desc->name, name))
            return desc;
    return NULL;
}