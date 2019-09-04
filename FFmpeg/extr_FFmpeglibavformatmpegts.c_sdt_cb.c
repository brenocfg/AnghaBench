#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_16__ {int /*<<< orphan*/  stream; scalar_t__ skip_changes; } ;
struct TYPE_14__ {TYPE_5__* opaque; } ;
struct TYPE_12__ {TYPE_3__ section_filter; } ;
struct TYPE_15__ {TYPE_1__ u; } ;
struct TYPE_13__ {scalar_t__ tid; } ;
typedef  TYPE_2__ SectionHeader ;
typedef  TYPE_3__ MpegTSSectionFilter ;
typedef  TYPE_4__ MpegTSFilter ;
typedef  TYPE_5__ MpegTSContext ;
typedef  TYPE_6__ AVProgram ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ SDT_TID ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_6__* av_new_program (int /*<<< orphan*/ ,int) ; 
 int get16 (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int get8 (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 char* getstr8 (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hex_dump_debug (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ parse_section_header (TYPE_2__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ skip_identical (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void sdt_cb(MpegTSFilter *filter, const uint8_t *section, int section_len)
{
    MpegTSContext *ts = filter->u.section_filter.opaque;
    MpegTSSectionFilter *tssf = &filter->u.section_filter;
    SectionHeader h1, *h = &h1;
    const uint8_t *p, *p_end, *desc_list_end, *desc_end;
    int onid, val, sid, desc_list_len, desc_tag, desc_len, service_type;
    char *name, *provider_name;

    av_log(ts->stream, AV_LOG_TRACE, "SDT:\n");
    hex_dump_debug(ts->stream, section, section_len);

    p_end = section + section_len - 4;
    p     = section;
    if (parse_section_header(h, &p, p_end) < 0)
        return;
    if (h->tid != SDT_TID)
        return;
    if (ts->skip_changes)
        return;
    if (skip_identical(h, tssf))
        return;

    onid = get16(&p, p_end);
    if (onid < 0)
        return;
    val = get8(&p, p_end);
    if (val < 0)
        return;
    for (;;) {
        sid = get16(&p, p_end);
        if (sid < 0)
            break;
        val = get8(&p, p_end);
        if (val < 0)
            break;
        desc_list_len = get16(&p, p_end);
        if (desc_list_len < 0)
            break;
        desc_list_len &= 0xfff;
        desc_list_end  = p + desc_list_len;
        if (desc_list_end > p_end)
            break;
        for (;;) {
            desc_tag = get8(&p, desc_list_end);
            if (desc_tag < 0)
                break;
            desc_len = get8(&p, desc_list_end);
            desc_end = p + desc_len;
            if (desc_len < 0 || desc_end > desc_list_end)
                break;

            av_log(ts->stream, AV_LOG_TRACE, "tag: 0x%02x len=%d\n",
                    desc_tag, desc_len);

            switch (desc_tag) {
            case 0x48:
                service_type = get8(&p, p_end);
                if (service_type < 0)
                    break;
                provider_name = getstr8(&p, p_end);
                if (!provider_name)
                    break;
                name = getstr8(&p, p_end);
                if (name) {
                    AVProgram *program = av_new_program(ts->stream, sid);
                    if (program) {
                        av_dict_set(&program->metadata, "service_name", name, 0);
                        av_dict_set(&program->metadata, "service_provider",
                                    provider_name, 0);
                    }
                }
                av_free(name);
                av_free(provider_name);
                break;
            default:
                break;
            }
            p = desc_end;
        }
        p = desc_list_end;
    }
}