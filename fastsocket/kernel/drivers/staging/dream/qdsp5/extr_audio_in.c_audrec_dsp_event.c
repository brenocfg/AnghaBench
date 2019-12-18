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
typedef  unsigned int uint16_t ;
struct audio_in {int running; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 unsigned int AUDREC_MSG_CFG_DONE_TYPE_0_ENA ; 
 unsigned int AUDREC_MSG_CFG_DONE_TYPE_0_UPDATE ; 
#define  AUDREC_MSG_CMD_AREC_PARAM_CFG_DONE_MSG 131 
#define  AUDREC_MSG_CMD_CFG_DONE_MSG 130 
#define  AUDREC_MSG_FATAL_ERR_MSG 129 
#define  AUDREC_MSG_PACKET_READY_MSG 128 
 int /*<<< orphan*/  audio_dsp_set_agc (struct audio_in*) ; 
 int /*<<< orphan*/  audio_dsp_set_ns (struct audio_in*) ; 
 int /*<<< orphan*/  audio_dsp_set_tx_iir (struct audio_in*) ; 
 int /*<<< orphan*/  audio_in_encoder_config (struct audio_in*) ; 
 int /*<<< orphan*/  audio_in_get_dsp_frames (struct audio_in*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void audrec_dsp_event(void *data, unsigned id, size_t len,
			    void (*getevent)(void *ptr, size_t len))
{
	struct audio_in *audio = data;
	uint16_t msg[3];
	getevent(msg, sizeof(msg));

	switch (id) {
	case AUDREC_MSG_CMD_CFG_DONE_MSG:
		if (msg[0] & AUDREC_MSG_CFG_DONE_TYPE_0_UPDATE) {
			if (msg[0] & AUDREC_MSG_CFG_DONE_TYPE_0_ENA) {
				pr_info("audpre: CFG ENABLED\n");
				audio_dsp_set_agc(audio);
				audio_dsp_set_ns(audio);
				audio_dsp_set_tx_iir(audio);
				audio_in_encoder_config(audio);
			} else {
				pr_info("audrec: CFG SLEEP\n");
				audio->running = 0;
			}
		} else {
			pr_info("audrec: CMD_CFG_DONE %x\n", msg[0]);
		}
		break;
	case AUDREC_MSG_CMD_AREC_PARAM_CFG_DONE_MSG: {
		pr_info("audrec: PARAM CFG DONE\n");
		audio->running = 1;
		break;
	}
	case AUDREC_MSG_FATAL_ERR_MSG:
		pr_err("audrec: ERROR %x\n", msg[0]);
		break;
	case AUDREC_MSG_PACKET_READY_MSG:
/* REC_DBG("type %x, count %d", msg[0], (msg[1] | (msg[2] << 16))); */
		audio_in_get_dsp_frames(audio);
		break;
	default:
		pr_err("audrec: unknown event %d\n", id);
	}
}