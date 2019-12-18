#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_33__ {int program_num; int pmt_pid; } ;
struct TYPE_32__ {int current_pid; int nb_prg; TYPE_17__* stream; int /*<<< orphan*/  skip_clear; TYPE_2__* prg; TYPE_6__** pids; scalar_t__ skip_changes; } ;
struct TYPE_30__ {scalar_t__ section_cb; TYPE_7__* opaque; } ;
struct TYPE_26__ {TYPE_5__ section_filter; } ;
struct TYPE_31__ {scalar_t__ type; int pid; TYPE_1__ u; } ;
struct TYPE_29__ {scalar_t__ tid; int /*<<< orphan*/  id; } ;
struct TYPE_28__ {scalar_t__ id; } ;
struct TYPE_27__ {scalar_t__ id; } ;
struct TYPE_25__ {int nb_programs; TYPE_3__** programs; int /*<<< orphan*/  ts_id; } ;
typedef  TYPE_4__ SectionHeader ;
typedef  TYPE_5__ MpegTSSectionFilter ;
typedef  TYPE_6__ MpegTSFilter ;
typedef  TYPE_7__ MpegTSContext ;
typedef  TYPE_8__ AVProgram ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ MPEGTS_SECTION ; 
 scalar_t__ PAT_TID ; 
 int /*<<< orphan*/  add_pat_entry (TYPE_7__*,int) ; 
 int /*<<< orphan*/  add_pid_to_pmt (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_17__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_8__* av_new_program (TYPE_17__*,int) ; 
 int /*<<< orphan*/  clear_avprogram (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  clear_programs (TYPE_7__*) ; 
 int get16 (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hex_dump_debug (TYPE_17__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mpegts_close_filter (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mpegts_open_section_filter (TYPE_7__*,int,scalar_t__,TYPE_7__*,int) ; 
 scalar_t__ parse_section_header (TYPE_4__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ pmt_cb ; 
 scalar_t__ skip_identical (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static void pat_cb(MpegTSFilter *filter, const uint8_t *section, int section_len)
{
    MpegTSContext *ts = filter->u.section_filter.opaque;
    MpegTSSectionFilter *tssf = &filter->u.section_filter;
    SectionHeader h1, *h = &h1;
    const uint8_t *p, *p_end;
    int sid, pmt_pid;
    AVProgram *program;

    av_log(ts->stream, AV_LOG_TRACE, "PAT:\n");
    hex_dump_debug(ts->stream, section, section_len);

    p_end = section + section_len - 4;
    p     = section;
    if (parse_section_header(h, &p, p_end) < 0)
        return;
    if (h->tid != PAT_TID)
        return;
    if (ts->skip_changes)
        return;

    if (skip_identical(h, tssf))
        return;
    ts->stream->ts_id = h->id;

    clear_programs(ts);
    for (;;) {
        sid = get16(&p, p_end);
        if (sid < 0)
            break;
        pmt_pid = get16(&p, p_end);
        if (pmt_pid < 0)
            break;
        pmt_pid &= 0x1fff;

        if (pmt_pid == ts->current_pid)
            break;

        av_log(ts->stream, AV_LOG_TRACE, "sid=0x%x pid=0x%x\n", sid, pmt_pid);

        if (sid == 0x0000) {
            /* NIT info */
        } else {
            MpegTSFilter *fil = ts->pids[pmt_pid];
            program = av_new_program(ts->stream, sid);
            if (program) {
                program->program_num = sid;
                program->pmt_pid = pmt_pid;
            }
            if (fil)
                if (   fil->type != MPEGTS_SECTION
                    || fil->pid != pmt_pid
                    || fil->u.section_filter.section_cb != pmt_cb)
                    mpegts_close_filter(ts, ts->pids[pmt_pid]);

            if (!ts->pids[pmt_pid])
                mpegts_open_section_filter(ts, pmt_pid, pmt_cb, ts, 1);
            add_pat_entry(ts, sid);
            add_pid_to_pmt(ts, sid, 0); // add pat pid to program
            add_pid_to_pmt(ts, sid, pmt_pid);
        }
    }

    if (sid < 0) {
        int i,j;
        for (j=0; j<ts->stream->nb_programs; j++) {
            for (i = 0; i < ts->nb_prg; i++)
                if (ts->prg[i].id == ts->stream->programs[j]->id)
                    break;
            if (i==ts->nb_prg && !ts->skip_clear)
                clear_avprogram(ts, ts->stream->programs[j]->id);
        }
    }
}