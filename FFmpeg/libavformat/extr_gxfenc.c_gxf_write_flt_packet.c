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
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int nb_fields; int* flt_entries; } ;
typedef  TYPE_1__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_FLT ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gxf_write_packet_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int updatePacketSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_flt_packet(AVFormatContext *s)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t pos = avio_tell(pb);
    int fields_per_flt = (gxf->nb_fields+1) / 1000 + 1;
    int flt_entries = gxf->nb_fields / fields_per_flt;
    int i = 0;

    gxf_write_packet_header(pb, PKT_FLT);

    avio_wl32(pb, fields_per_flt); /* number of fields */
    avio_wl32(pb, flt_entries); /* number of active flt entries */

    if (gxf->flt_entries) {
        for (i = 0; i < flt_entries; i++)
            avio_wl32(pb, gxf->flt_entries[(i*fields_per_flt)>>1]);
    }

    for (; i < 1000; i++)
        avio_wl32(pb, 0);

    return updatePacketSize(pb, pos);
}