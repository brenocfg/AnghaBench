#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  ff_asf_guid ;
struct TYPE_12__ {scalar_t__ offset; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_10__ {int (* read_object ) (TYPE_2__*,TYPE_1__ const*) ;char* name; int is_subobject; } ;
typedef  TYPE_1__ GUIDParseTable ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int /*<<< orphan*/  asf_read_unknown (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int ff_get_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* find_guid (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,TYPE_1__ const*) ; 

__attribute__((used)) static int detect_unknown_subobject(AVFormatContext *s, int64_t offset, int64_t size)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    const GUIDParseTable *g = NULL;
    ff_asf_guid guid;
    int ret;

    while (avio_tell(pb) <= offset + size) {
        if (avio_tell(pb) == asf->offset)
            break;
        asf->offset = avio_tell(pb);
        if ((ret = ff_get_guid(pb, &guid)) < 0)
            return ret;
        g = find_guid(guid);
        if (g) {
            if ((ret = g->read_object(s, g)) < 0)
                return ret;
        } else {
            GUIDParseTable g2;

            g2.name         = "Unknown";
            g2.is_subobject = 1;
            asf_read_unknown(s, &g2);
        }
    }

    return 0;
}