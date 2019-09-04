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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  device_ref; int /*<<< orphan*/  frames_ref; int /*<<< orphan*/ * frame_group; int /*<<< orphan*/ * ctx; TYPE_1__* mpi; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ RKMPPDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mpp_buffer_group_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rkmpp_release_decoder(void *opaque, uint8_t *data)
{
    RKMPPDecoder *decoder = (RKMPPDecoder *)data;

    if (decoder->mpi) {
        decoder->mpi->reset(decoder->ctx);
        mpp_destroy(decoder->ctx);
        decoder->ctx = NULL;
    }

    if (decoder->frame_group) {
        mpp_buffer_group_put(decoder->frame_group);
        decoder->frame_group = NULL;
    }

    av_buffer_unref(&decoder->frames_ref);
    av_buffer_unref(&decoder->device_ref);

    av_free(decoder);
}