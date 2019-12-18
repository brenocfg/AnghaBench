#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_14__ {int /*<<< orphan*/  pb; } ;
struct TYPE_13__ {TYPE_1__* priv_data; } ;
struct TYPE_12__ {scalar_t__ avc_intra; } ;
typedef  TYPE_1__ MXFStreamContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  mxf_cdci_descriptor_key ; 
 int /*<<< orphan*/  mxf_update_klv_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_avc_subdesc (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mxf_write_cdci_common (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_mpegvideo_desc (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void mxf_write_h264_desc(AVFormatContext *s, AVStream *st)
{
    MXFStreamContext *sc = st->priv_data;
    if (sc->avc_intra) {
        mxf_write_mpegvideo_desc(s, st);
    } else {
        int64_t pos = mxf_write_cdci_common(s, st, mxf_cdci_descriptor_key);
        mxf_update_klv_size(s->pb, pos);
        mxf_write_avc_subdesc(s, st);
    }
}