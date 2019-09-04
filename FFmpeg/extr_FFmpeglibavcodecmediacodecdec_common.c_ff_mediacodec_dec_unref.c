#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* codec_name; int /*<<< orphan*/ * surface; int /*<<< orphan*/ * format; int /*<<< orphan*/ * codec; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ MediaCodecDecContext ;

/* Variables and functions */
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  ff_AMediaCodec_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_AMediaFormat_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mediacodec_surface_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ff_mediacodec_dec_unref(MediaCodecDecContext *s)
{
    if (!s)
        return;

    if (atomic_fetch_sub(&s->refcount, 1) == 1) {
        if (s->codec) {
            ff_AMediaCodec_delete(s->codec);
            s->codec = NULL;
        }

        if (s->format) {
            ff_AMediaFormat_delete(s->format);
            s->format = NULL;
        }

        if (s->surface) {
            ff_mediacodec_surface_unref(s->surface, NULL);
            s->surface = NULL;
        }

        av_freep(&s->codec_name);
        av_freep(&s);
    }
}