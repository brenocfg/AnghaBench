#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int structural_components_count; int /*<<< orphan*/ * structural_components_refs; } ;
struct TYPE_8__ {int /*<<< orphan*/  descriptor_ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  source_package_uid; int /*<<< orphan*/  source_package_ul; } ;
typedef  TYPE_1__ MXFStructuralComponent ;
typedef  TYPE_2__ MXFPackage ;
typedef  TYPE_3__ MXFEssenceGroup ;
typedef  int /*<<< orphan*/  MXFDescriptor ;
typedef  int /*<<< orphan*/  MXFContext ;

/* Variables and functions */
 int /*<<< orphan*/  Descriptor ; 
 int /*<<< orphan*/  SourceClip ; 
 TYPE_2__* mxf_resolve_source_package (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mxf_resolve_strong_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MXFStructuralComponent* mxf_resolve_essence_group_choice(MXFContext *mxf, MXFEssenceGroup *essence_group)
{
    MXFStructuralComponent *component = NULL;
    MXFPackage *package = NULL;
    MXFDescriptor *descriptor = NULL;
    int i;

    if (!essence_group || !essence_group->structural_components_count)
        return NULL;

    /* essence groups contains multiple representations of the same media,
       this return the first components with a valid Descriptor typically index 0 */
    for (i =0; i < essence_group->structural_components_count; i++){
        component = mxf_resolve_strong_ref(mxf, &essence_group->structural_components_refs[i], SourceClip);
        if (!component)
            continue;

        if (!(package = mxf_resolve_source_package(mxf, component->source_package_ul, component->source_package_uid)))
            continue;

        descriptor = mxf_resolve_strong_ref(mxf, &package->descriptor_ref, Descriptor);
        if (descriptor)
            return component;
    }
    return NULL;
}