#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvr2_stream_stats {int /*<<< orphan*/  buffers_failed; int /*<<< orphan*/  buffers_processed; int /*<<< orphan*/  buffers_in_ready; int /*<<< orphan*/  buffers_in_idle; int /*<<< orphan*/  buffers_in_queue; int /*<<< orphan*/  bytes_processed; } ;
struct pvr2_hdw {unsigned int ir_scheme_active; int /*<<< orphan*/  vid_stream; int /*<<< orphan*/  input_allowed_mask; int /*<<< orphan*/  input_avail_mask; int /*<<< orphan*/  master_state; int /*<<< orphan*/  state_pathway_ok; int /*<<< orphan*/  state_usbstream_run; int /*<<< orphan*/  state_encoder_waitok; int /*<<< orphan*/  state_encoder_config; int /*<<< orphan*/  state_encoder_runok; int /*<<< orphan*/  state_encoder_run; int /*<<< orphan*/  state_encoder_ok; int /*<<< orphan*/  state_decoder_quiescent; int /*<<< orphan*/  state_decoder_ready; int /*<<< orphan*/  state_decoder_run; int /*<<< orphan*/  state_pipeline_pause; int /*<<< orphan*/  state_pipeline_req; int /*<<< orphan*/  state_pipeline_config; int /*<<< orphan*/  state_pipeline_idle; int /*<<< orphan*/  pathway_state; int /*<<< orphan*/  flag_decoder_missed; int /*<<< orphan*/  flag_tripped; int /*<<< orphan*/  flag_disconnected; int /*<<< orphan*/  flag_init_ok; int /*<<< orphan*/  flag_ok; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 char** ir_scheme_names ; 
 unsigned int print_input_mask (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  pvr2_get_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_pathway_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_stream_get_stats (int /*<<< orphan*/ ,struct pvr2_stream_stats*,int /*<<< orphan*/ ) ; 
 unsigned int scnprintf (char*,unsigned int,char*,...) ; 

__attribute__((used)) static unsigned int pvr2_hdw_report_unlocked(struct pvr2_hdw *hdw,int which,
					     char *buf,unsigned int acnt)
{
	switch (which) {
	case 0:
		return scnprintf(
			buf,acnt,
			"driver:%s%s%s%s%s <mode=%s>",
			(hdw->flag_ok ? " <ok>" : " <fail>"),
			(hdw->flag_init_ok ? " <init>" : " <uninitialized>"),
			(hdw->flag_disconnected ? " <disconnected>" :
			 " <connected>"),
			(hdw->flag_tripped ? " <tripped>" : ""),
			(hdw->flag_decoder_missed ? " <no decoder>" : ""),
			pvr2_pathway_state_name(hdw->pathway_state));

	case 1:
		return scnprintf(
			buf,acnt,
			"pipeline:%s%s%s%s",
			(hdw->state_pipeline_idle ? " <idle>" : ""),
			(hdw->state_pipeline_config ?
			 " <configok>" : " <stale>"),
			(hdw->state_pipeline_req ? " <req>" : ""),
			(hdw->state_pipeline_pause ? " <pause>" : ""));
	case 2:
		return scnprintf(
			buf,acnt,
			"worker:%s%s%s%s%s%s%s",
			(hdw->state_decoder_run ?
			 (hdw->state_decoder_ready ?
			  "<decode:run>" : " <decode:start>") :
			 (hdw->state_decoder_quiescent ?
			  "" : " <decode:stop>")),
			(hdw->state_decoder_quiescent ?
			 " <decode:quiescent>" : ""),
			(hdw->state_encoder_ok ?
			 "" : " <encode:init>"),
			(hdw->state_encoder_run ?
			 (hdw->state_encoder_runok ?
			  " <encode:run>" :
			  " <encode:firstrun>") :
			 (hdw->state_encoder_runok ?
			  " <encode:stop>" :
			  " <encode:virgin>")),
			(hdw->state_encoder_config ?
			 " <encode:configok>" :
			 (hdw->state_encoder_waitok ?
			  "" : " <encode:waitok>")),
			(hdw->state_usbstream_run ?
			 " <usb:run>" : " <usb:stop>"),
			(hdw->state_pathway_ok ?
			 " <pathway:ok>" : ""));
	case 3:
		return scnprintf(
			buf,acnt,
			"state: %s",
			pvr2_get_state_name(hdw->master_state));
	case 4: {
		unsigned int tcnt = 0;
		unsigned int ccnt;

		ccnt = scnprintf(buf,
				 acnt,
				 "Hardware supported inputs: ");
		tcnt += ccnt;
		tcnt += print_input_mask(hdw->input_avail_mask,
					 buf+tcnt,
					 acnt-tcnt);
		if (hdw->input_avail_mask != hdw->input_allowed_mask) {
			ccnt = scnprintf(buf+tcnt,
					 acnt-tcnt,
					 "; allowed inputs: ");
			tcnt += ccnt;
			tcnt += print_input_mask(hdw->input_allowed_mask,
						 buf+tcnt,
						 acnt-tcnt);
		}
		return tcnt;
	}
	case 5: {
		struct pvr2_stream_stats stats;
		if (!hdw->vid_stream) break;
		pvr2_stream_get_stats(hdw->vid_stream,
				      &stats,
				      0);
		return scnprintf(
			buf,acnt,
			"Bytes streamed=%u"
			" URBs: queued=%u idle=%u ready=%u"
			" processed=%u failed=%u",
			stats.bytes_processed,
			stats.buffers_in_queue,
			stats.buffers_in_idle,
			stats.buffers_in_ready,
			stats.buffers_processed,
			stats.buffers_failed);
	}
	case 6: {
		unsigned int id = hdw->ir_scheme_active;
		return scnprintf(buf, acnt, "ir scheme: id=%d %s", id,
				 (id >= ARRAY_SIZE(ir_scheme_names) ?
				  "?" : ir_scheme_names[id]));
	}
	default: break;
	}
	return 0;
}