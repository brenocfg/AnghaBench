#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int text; } ;
typedef  TYPE_5__ json_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  progress; } ;
struct TYPE_10__ {int /*<<< orphan*/  error; int /*<<< orphan*/  seconds; int /*<<< orphan*/  paused; int /*<<< orphan*/  minutes; int /*<<< orphan*/  hours; int /*<<< orphan*/  eta_seconds; int /*<<< orphan*/  rate_avg; int /*<<< orphan*/  rate_cur; int /*<<< orphan*/  pass_count; int /*<<< orphan*/  pass; int /*<<< orphan*/  pass_id; int /*<<< orphan*/  progress; } ;
struct TYPE_9__ {int /*<<< orphan*/  title_count; int /*<<< orphan*/  title_cur; int /*<<< orphan*/  preview_count; int /*<<< orphan*/  preview_cur; int /*<<< orphan*/  progress; } ;
struct TYPE_12__ {TYPE_3__ muxing; TYPE_2__ working; TYPE_1__ scanning; } ;
struct TYPE_14__ {int state; TYPE_4__ param; int /*<<< orphan*/  sequence_id; } ;
typedef  TYPE_6__ hb_state_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
#define  HB_STATE_IDLE 135 
#define  HB_STATE_MUXING 134 
#define  HB_STATE_PAUSED 133 
#define  HB_STATE_SCANDONE 132 
#define  HB_STATE_SCANNING 131 
#define  HB_STATE_SEARCHING 130 
#define  HB_STATE_WORKDONE 129 
#define  HB_STATE_WORKING 128 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 int /*<<< orphan*/  hb_value_double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_string (char const*) ; 
 int /*<<< orphan*/ * json_pack_ex (TYPE_5__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 

hb_dict_t* hb_state_to_dict( hb_state_t * state)
{
    const char * state_s;
    hb_dict_t *dict = NULL;
    json_error_t error;

    switch (state->state)
    {
    case HB_STATE_IDLE:
        state_s = "IDLE";
        break;
    case HB_STATE_SCANNING:
        state_s = "SCANNING";
        break;
    case HB_STATE_SCANDONE:
        state_s = "SCANDONE";
        break;
    case HB_STATE_WORKING:
        state_s = "WORKING";
        break;
    case HB_STATE_PAUSED:
        state_s = "PAUSED";
        break;
    case HB_STATE_SEARCHING:
        state_s = "SEARCHING";
        break;
    case HB_STATE_WORKDONE:
        state_s = "WORKDONE";
        break;
    case HB_STATE_MUXING:
        state_s = "MUXING";
        break;
    default:
        state_s = "UNKNOWN";
        break;
    }

    switch (state->state)
    {
    case HB_STATE_IDLE:
        dict = json_pack_ex(&error, 0, "{s:o}",
                    "State", hb_value_string(state_s));
        break;
    case HB_STATE_SCANNING:
    case HB_STATE_SCANDONE:
        dict = json_pack_ex(&error, 0,
            "{s:o, s{s:o, s:o, s:o, s:o, s:o, s:o}}",
            "State", hb_value_string(state_s),
            "Scanning",
                "SequenceID",   hb_value_int(state->sequence_id),
                "Progress",     hb_value_double(state->param.scanning.progress),
                "Preview",      hb_value_int(state->param.scanning.preview_cur),
                "PreviewCount", hb_value_int(state->param.scanning.preview_count),
                "Title",        hb_value_int(state->param.scanning.title_cur),
                "TitleCount",   hb_value_int(state->param.scanning.title_count));
        break;
    case HB_STATE_WORKING:
    case HB_STATE_PAUSED:
    case HB_STATE_SEARCHING:
        dict = json_pack_ex(&error, 0,
            "{s:o, s{s:o, s:o, s:o, s:o, s:o, s:o,"
                   " s:o, s:o, s:o, s:o, s:o, s:o}}",
            "State", hb_value_string(state_s),
            "Working",
                "Progress",     hb_value_double(state->param.working.progress),
                "PassID",       hb_value_int(state->param.working.pass_id),
                "Pass",         hb_value_int(state->param.working.pass),
                "PassCount",    hb_value_int(state->param.working.pass_count),
                "Rate",         hb_value_double(state->param.working.rate_cur),
                "RateAvg",      hb_value_double(state->param.working.rate_avg),
                "ETASeconds",   hb_value_int(state->param.working.eta_seconds),
                "Hours",        hb_value_int(state->param.working.hours),
                "Minutes",      hb_value_int(state->param.working.minutes),
                "Paused",       hb_value_int(state->param.working.paused),
                "Seconds",      hb_value_int(state->param.working.seconds),
                "SequenceID",   hb_value_int(state->sequence_id));
        break;
    case HB_STATE_WORKDONE:
        dict = json_pack_ex(&error, 0,
            "{s:o, s{s:o, s:o}}",
            "State", hb_value_string(state_s),
            "WorkDone",
                "SequenceID",   hb_value_int(state->sequence_id),
                "Error",        hb_value_int(state->param.working.error));
        break;
    case HB_STATE_MUXING:
        dict = json_pack_ex(&error, 0,
            "{s:o, s{s:o}}",
            "State", hb_value_string(state_s),
            "Muxing",
                "Progress", hb_value_double(state->param.muxing.progress));
        break;
    default:
        dict = json_pack_ex(&error, 0, "{s:o}",
                    "State", hb_value_string(state_s));
        hb_error("hb_state_to_dict: unrecognized state %d", state->state);
        break;
    }
    if (dict == NULL)
    {
        hb_error("json pack failure: %s", error.text);
    }
    return dict;
}