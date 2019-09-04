#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVCodecDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__ const* avcodec_descriptor_get (scalar_t__) ; 
 TYPE_1__ const* avcodec_descriptor_get_by_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* avcodec_descriptor_next (TYPE_1__ const*) ; 

int main(int argc, char **argv)
{
    const AVCodecDescriptor *old_desc = NULL, *desc;

    while (desc = avcodec_descriptor_next(old_desc)) {
        if (old_desc && old_desc->id >= desc->id) {
            av_log(NULL, AV_LOG_FATAL, "Unsorted codec_descriptors '%s' and '%s'.\n", old_desc->name, desc->name);
            return 1;
        }

        if (avcodec_descriptor_get(desc->id) != desc) {
            av_log(NULL, AV_LOG_FATAL, "avcodec_descriptor_get() failed with '%s'.\n", desc->name);
            return 1;
        }

        if (avcodec_descriptor_get_by_name(desc->name) != desc) {
            av_log(NULL, AV_LOG_FATAL, "avcodec_descriptor_get_by_name() failed with '%s'.\n", desc->name);
            return 1;
        }

        old_desc = desc;
    }

    return 0;
}