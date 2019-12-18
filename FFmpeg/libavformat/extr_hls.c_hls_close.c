#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  playlist_pb; int /*<<< orphan*/  ctx; int /*<<< orphan*/  avio_opts; } ;
typedef  TYPE_1__ HLSContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_format_io_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_playlist_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_rendition_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_variant_list (TYPE_1__*) ; 

__attribute__((used)) static int hls_close(AVFormatContext *s)
{
    HLSContext *c = s->priv_data;

    free_playlist_list(c);
    free_variant_list(c);
    free_rendition_list(c);

    av_dict_free(&c->avio_opts);
    ff_format_io_close(c->ctx, &c->playlist_pb);

    return 0;
}