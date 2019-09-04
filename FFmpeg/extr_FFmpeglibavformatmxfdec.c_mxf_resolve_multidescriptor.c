#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fc; } ;
struct TYPE_8__ {scalar_t__ type; int sub_descriptors_count; int linked_track_id; int /*<<< orphan*/ * sub_descriptors_refs; } ;
typedef  TYPE_1__ MXFDescriptor ;
typedef  TYPE_2__ MXFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ Descriptor ; 
 scalar_t__ MultipleDescriptor ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mxf_resolve_strong_ref (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static MXFDescriptor* mxf_resolve_multidescriptor(MXFContext *mxf, MXFDescriptor *descriptor, int track_id)
{
    MXFDescriptor *sub_descriptor = NULL;
    int i;

    if (!descriptor)
        return NULL;

    if (descriptor->type == MultipleDescriptor) {
        for (i = 0; i < descriptor->sub_descriptors_count; i++) {
            sub_descriptor = mxf_resolve_strong_ref(mxf, &descriptor->sub_descriptors_refs[i], Descriptor);

            if (!sub_descriptor) {
                av_log(mxf->fc, AV_LOG_ERROR, "could not resolve sub descriptor strong ref\n");
                continue;
            }
            if (sub_descriptor->linked_track_id == track_id) {
                return sub_descriptor;
            }
        }
    } else if (descriptor->type == Descriptor)
        return descriptor;

    return NULL;
}