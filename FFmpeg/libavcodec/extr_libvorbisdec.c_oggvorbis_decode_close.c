#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  vc; int /*<<< orphan*/  vi; int /*<<< orphan*/  vd; int /*<<< orphan*/  vb; } ;
typedef  TYPE_1__ OggVorbisDecContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  vorbis_block_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_comment_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_dsp_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_info_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oggvorbis_decode_close(AVCodecContext *avccontext) {
    OggVorbisDecContext *context = avccontext->priv_data ;

    vorbis_block_clear(&context->vb);
    vorbis_dsp_clear(&context->vd);
    vorbis_info_clear(&context->vi) ;
    vorbis_comment_clear(&context->vc) ;

    return 0 ;
}