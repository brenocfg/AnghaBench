#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {size_t index; } ;
struct TYPE_6__ {unsigned int mlti_data_size; int /*<<< orphan*/ * rmst; int /*<<< orphan*/  rmctx; int /*<<< orphan*/  mlti_data; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ff_rm_read_mdpr_codecdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_init_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rdt_load_mdpr (PayloadContext *rdt, AVStream *st, int rule_nr)
{
    AVIOContext pb;
    unsigned int size;
    uint32_t tag;

    /**
     * Layout of the MLTI chunk:
     * 4: MLTI
     * 2: number of streams
     * Then for each stream ([number_of_streams] times):
     *     2: mdpr index
     * 2: number of mdpr chunks
     * Then for each mdpr chunk ([number_of_mdpr_chunks] times):
     *     4: size
     *     [size]: data
     * we skip MDPR chunks until we reach the one of the stream
     * we're interested in, and forward that ([size]+[data]) to
     * the RM demuxer to parse the stream-specific header data.
     */
    if (!rdt->mlti_data)
        return -1;
    ffio_init_context(&pb, rdt->mlti_data, rdt->mlti_data_size, 0,
                  NULL, NULL, NULL, NULL);
    tag = avio_rl32(&pb);
    if (tag == MKTAG('M', 'L', 'T', 'I')) {
        int num, chunk_nr;

        /* read index of MDPR chunk numbers */
        num = avio_rb16(&pb);
        if (rule_nr < 0 || rule_nr >= num)
            return -1;
        avio_skip(&pb, rule_nr * 2);
        chunk_nr = avio_rb16(&pb);
        avio_skip(&pb, (num - 1 - rule_nr) * 2);

        /* read MDPR chunks */
        num = avio_rb16(&pb);
        if (chunk_nr >= num)
            return -1;
        while (chunk_nr--)
            avio_skip(&pb, avio_rb32(&pb));
        size = avio_rb32(&pb);
    } else {
        size = rdt->mlti_data_size;
        avio_seek(&pb, 0, SEEK_SET);
    }
    if (ff_rm_read_mdpr_codecdata(rdt->rmctx, &pb, st, rdt->rmst[st->index], size, NULL) < 0)
        return -1;

    return 0;
}