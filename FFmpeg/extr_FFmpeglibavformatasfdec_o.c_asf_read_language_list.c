#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  offset; TYPE_1__* asf_sd; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  langs; } ;
typedef  int /*<<< orphan*/  GUIDParseTable ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int ASF_MAX_STREAMS ; 
 int /*<<< orphan*/  align_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ *) ; 
 int get_asf_string (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int asf_read_language_list(AVFormatContext *s, const GUIDParseTable *g)
{
    ASFContext *asf   = s->priv_data;
    AVIOContext *pb   = s->pb;
    int i, ret;
    uint64_t size     = avio_rl64(pb);
    uint16_t nb_langs = avio_rl16(pb);

    if (nb_langs < ASF_MAX_STREAMS) {
        for (i = 0; i < nb_langs; i++) {
            size_t len;
            len = avio_r8(pb);
            if (!len)
                len = 6;
            if ((ret = get_asf_string(pb, len, asf->asf_sd[i].langs,
                                      sizeof(asf->asf_sd[i].langs))) < 0) {
                return ret;
            }
        }
    }

    align_position(pb, asf->offset, size);
    return 0;
}