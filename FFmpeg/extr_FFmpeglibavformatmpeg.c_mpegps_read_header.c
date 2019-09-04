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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_5__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  ctx_flags; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int header_state; int imkh_cctv; int sofdec; } ;
typedef  TYPE_1__ MpegDemuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_get_str (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

__attribute__((used)) static int mpegps_read_header(AVFormatContext *s)
{
    MpegDemuxContext *m = s->priv_data;
    char buffer[7] = { 0 };
    int64_t last_pos = avio_tell(s->pb);

    m->header_state = 0xff;
    s->ctx_flags   |= AVFMTCTX_NOHEADER;

    avio_get_str(s->pb, 6, buffer, sizeof(buffer));
    if (!memcmp("IMKH", buffer, 4)) {
        m->imkh_cctv = 1;
    } else if (!memcmp("Sofdec", buffer, 6)) {
        m->sofdec = 1;
    } else
       avio_seek(s->pb, last_pos, SEEK_SET);

    /* no need to do more */
    return 0;
}