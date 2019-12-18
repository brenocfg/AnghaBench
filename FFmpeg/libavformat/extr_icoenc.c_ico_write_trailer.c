#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_10__ {int current_image; int nb_images; TYPE_3__* images; } ;
struct TYPE_9__ {int width; int height; int bits; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {scalar_t__ codec_id; scalar_t__ format; } ;
typedef  TYPE_4__ IcoMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_BMP ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ico_write_trailer(AVFormatContext *s)
{
    IcoMuxContext *ico = s->priv_data;
    AVIOContext *pb = s->pb;
    int i;

    avio_seek(pb, 4, SEEK_SET);

    avio_wl16(pb, ico->current_image);

    for (i = 0; i < ico->nb_images; i++) {
        avio_w8(pb, ico->images[i].width);
        avio_w8(pb, ico->images[i].height);

        if (s->streams[i]->codecpar->codec_id == AV_CODEC_ID_BMP &&
            s->streams[i]->codecpar->format == AV_PIX_FMT_PAL8) {
            avio_w8(pb, (ico->images[i].bits >= 8) ? 0 : 1 << ico->images[i].bits);
        } else {
            avio_w8(pb, 0);
        }

        avio_w8(pb, 0); // reserved
        avio_wl16(pb, 1); // color planes
        avio_wl16(pb, ico->images[i].bits);
        avio_wl32(pb, ico->images[i].size);
        avio_wl32(pb, ico->images[i].offset);
    }

    return 0;
}