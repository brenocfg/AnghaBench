#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; int nb_chapters; int nb_programs; TYPE_3__** programs; TYPE_2__** chapters; TYPE_1__** streams; int /*<<< orphan*/  metadata; } ;
struct TYPE_8__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_7__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVMetadataConv ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void ff_metadata_conv_ctx(AVFormatContext *ctx, const AVMetadataConv *d_conv,
                                                const AVMetadataConv *s_conv)
{
    int i;
    ff_metadata_conv(&ctx->metadata, d_conv, s_conv);
    for (i=0; i<ctx->nb_streams ; i++)
        ff_metadata_conv(&ctx->streams [i]->metadata, d_conv, s_conv);
    for (i=0; i<ctx->nb_chapters; i++)
        ff_metadata_conv(&ctx->chapters[i]->metadata, d_conv, s_conv);
    for (i=0; i<ctx->nb_programs; i++)
        ff_metadata_conv(&ctx->programs[i]->metadata, d_conv, s_conv);
}