#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__ const* ReferenceFrames; } ;
typedef  TYPE_1__ VAPictureParameterBufferHEVC ;
struct TYPE_14__ {TYPE_2__ const* DPB; TYPE_2__ const* ref; } ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_2__ const HEVCFrame ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_2__ const*) ; 
 int HEVC_FRAME_FLAG_LONG_REF ; 
 int HEVC_FRAME_FLAG_SHORT_REF ; 
 int /*<<< orphan*/  fill_vaapi_pic (TYPE_2__ const*,TYPE_2__ const*,int) ; 
 int find_frame_rps_type (TYPE_3__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  init_vaapi_pic (TYPE_2__ const*) ; 

__attribute__((used)) static void fill_vaapi_reference_frames(const HEVCContext *h, VAPictureParameterBufferHEVC *pp)
{
    const HEVCFrame *current_picture = h->ref;
    int i, j, rps_type;

    for (i = 0, j = 0; i < FF_ARRAY_ELEMS(pp->ReferenceFrames); i++) {
        const HEVCFrame *frame = NULL;

        while (!frame && j < FF_ARRAY_ELEMS(h->DPB)) {
            if (&h->DPB[j] != current_picture && (h->DPB[j].flags & (HEVC_FRAME_FLAG_LONG_REF | HEVC_FRAME_FLAG_SHORT_REF)))
                frame = &h->DPB[j];
            j++;
        }

        init_vaapi_pic(&pp->ReferenceFrames[i]);

        if (frame) {
            rps_type = find_frame_rps_type(h, frame);
            fill_vaapi_pic(&pp->ReferenceFrames[i], frame, rps_type);
        }
    }
}