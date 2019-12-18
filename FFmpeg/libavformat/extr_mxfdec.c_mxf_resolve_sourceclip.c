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
typedef  int /*<<< orphan*/  UID ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ MXFStructuralComponent ;
typedef  int /*<<< orphan*/  MXFEssenceGroup ;
typedef  int /*<<< orphan*/  MXFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AnyType ; 
#define  EssenceGroup 129 
#define  SourceClip 128 
 TYPE_1__* mxf_resolve_essence_group_choice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* mxf_resolve_strong_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MXFStructuralComponent* mxf_resolve_sourceclip(MXFContext *mxf, UID *strong_ref)
{
    MXFStructuralComponent *component = NULL;

    component = mxf_resolve_strong_ref(mxf, strong_ref, AnyType);
    if (!component)
        return NULL;
    switch (component->type) {
        case SourceClip:
            return component;
        case EssenceGroup:
            return mxf_resolve_essence_group_choice(mxf, (MXFEssenceGroup*) component);
        default:
            break;
    }
    return NULL;
}