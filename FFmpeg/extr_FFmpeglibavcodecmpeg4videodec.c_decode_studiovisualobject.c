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
struct TYPE_5__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int VOT_VIDEO_ID ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  extension_and_user_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next_start_code_studio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_studiovisualobject(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;
    int visual_object_type;

        skip_bits(gb, 4); /* visual_object_verid */
        visual_object_type = get_bits(gb, 4);
        if (visual_object_type != VOT_VIDEO_ID) {
            avpriv_request_sample(s->avctx, "VO type %u", visual_object_type);
            return AVERROR_PATCHWELCOME;
        }

        next_start_code_studio(gb);
        extension_and_user_data(s, gb, 1);

    return 0;
}