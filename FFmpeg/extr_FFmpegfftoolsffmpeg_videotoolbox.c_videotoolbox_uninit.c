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
struct TYPE_7__ {int /*<<< orphan*/  tmp_frame; } ;
typedef  TYPE_1__ VTContext ;
struct TYPE_9__ {TYPE_2__* opaque; } ;
struct TYPE_8__ {TYPE_1__* hwaccel_ctx; int /*<<< orphan*/ * hwaccel_retrieve_data; int /*<<< orphan*/ * hwaccel_uninit; } ;
typedef  TYPE_2__ InputStream ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_videotoolbox_default_free (TYPE_3__*) ; 

__attribute__((used)) static void videotoolbox_uninit(AVCodecContext *s)
{
    InputStream *ist = s->opaque;
    VTContext  *vt = ist->hwaccel_ctx;

    ist->hwaccel_uninit        = NULL;
    ist->hwaccel_retrieve_data = NULL;

    av_frame_free(&vt->tmp_frame);

    av_videotoolbox_default_free(s);
    av_freep(&ist->hwaccel_ctx);
}