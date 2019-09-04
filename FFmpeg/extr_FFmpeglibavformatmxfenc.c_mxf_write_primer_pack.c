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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  uid; int /*<<< orphan*/  local_tag; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int store_user_comments; } ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  klv_encode_ber_length (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* mxf_local_tag_batch ; 
 TYPE_4__* mxf_user_comments_local_tag ; 
 int /*<<< orphan*/  primer_pack_key ; 

__attribute__((used)) static void mxf_write_primer_pack(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int local_tag_number, i = 0;

    local_tag_number = FF_ARRAY_ELEMS(mxf_local_tag_batch);
    local_tag_number += mxf->store_user_comments * FF_ARRAY_ELEMS(mxf_user_comments_local_tag);

    avio_write(pb, primer_pack_key, 16);
    klv_encode_ber_length(pb, local_tag_number * 18 + 8);

    avio_wb32(pb, local_tag_number); // local_tag num
    avio_wb32(pb, 18); // item size, always 18 according to the specs

    for (i = 0; i < FF_ARRAY_ELEMS(mxf_local_tag_batch); i++) {
        avio_wb16(pb, mxf_local_tag_batch[i].local_tag);
        avio_write(pb, mxf_local_tag_batch[i].uid, 16);
    }
    if (mxf->store_user_comments)
        for (i = 0; i < FF_ARRAY_ELEMS(mxf_user_comments_local_tag); i++) {
            avio_wb16(pb, mxf_user_comments_local_tag[i].local_tag);
            avio_write(pb, mxf_user_comments_local_tag[i].uid, 16);
        }
}