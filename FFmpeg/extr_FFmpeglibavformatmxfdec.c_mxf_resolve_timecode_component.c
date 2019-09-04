#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UID ;
struct TYPE_7__ {int /*<<< orphan*/  input_segment_ref; } ;
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ MXFTimecodeComponent ;
typedef  TYPE_1__ MXFStructuralComponent ;
typedef  TYPE_3__ MXFPulldownComponent ;
typedef  int /*<<< orphan*/  MXFContext ;

/* Variables and functions */
 int const AnyType ; 
#define  PulldownComponent 129 
#define  TimecodeComponent 128 
 TYPE_1__* mxf_resolve_strong_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static MXFTimecodeComponent* mxf_resolve_timecode_component(MXFContext *mxf, UID *strong_ref)
{
    MXFStructuralComponent *component = NULL;
    MXFPulldownComponent *pulldown = NULL;

    component = mxf_resolve_strong_ref(mxf, strong_ref, AnyType);
    if (!component)
        return NULL;

    switch (component->type) {
    case TimecodeComponent:
        return (MXFTimecodeComponent*)component;
    case PulldownComponent: /* timcode component may be located on a pulldown component */
        pulldown = (MXFPulldownComponent*)component;
        return mxf_resolve_strong_ref(mxf, &pulldown->input_segment_ref, TimecodeComponent);
    default:
        break;
    }
    return NULL;
}