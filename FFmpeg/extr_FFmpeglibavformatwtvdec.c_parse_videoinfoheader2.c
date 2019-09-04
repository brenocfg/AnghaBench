#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * pb; } ;
typedef  TYPE_2__ WtvContext ;
struct TYPE_11__ {TYPE_2__* priv_data; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int /*<<< orphan*/  codec_tag; } ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_get_bmp_header (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_videoinfoheader2(AVFormatContext *s, AVStream *st)
{
    WtvContext *wtv = s->priv_data;
    AVIOContext *pb = wtv->pb;

    avio_skip(pb, 72);  // picture aspect ratio is unreliable
    st->codecpar->codec_tag = ff_get_bmp_header(pb, st, NULL);

    return 72 + 40;
}