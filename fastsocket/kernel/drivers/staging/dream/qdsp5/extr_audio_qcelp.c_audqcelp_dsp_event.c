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
struct audio {int running; int /*<<< orphan*/  dec_id; int /*<<< orphan*/  volume; int /*<<< orphan*/  out_needed; int /*<<< orphan*/  pcm_feedback; } ;

/* Variables and functions */
#define  AUDPP_DEC_STATUS_CFG 134 
#define  AUDPP_DEC_STATUS_INIT 133 
#define  AUDPP_DEC_STATUS_PLAY 132 
#define  AUDPP_DEC_STATUS_SLEEP 131 
#define  AUDPP_MSG_CFG_MSG 130 
 unsigned int AUDPP_MSG_ENA_DIS ; 
 unsigned int AUDPP_MSG_ENA_ENA ; 
#define  AUDPP_MSG_ROUTING_ACK 129 
#define  AUDPP_MSG_STATUS_MSG 128 
 int /*<<< orphan*/  auddec_dsp_config (struct audio*,int) ; 
 int /*<<< orphan*/  audpp_avsync (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  audpp_cmd_cfg_adec_params (struct audio*) ; 
 int /*<<< orphan*/  audpp_cmd_cfg_routing_mode (struct audio*) ; 
 int /*<<< orphan*/  audpp_set_volume_and_pan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audqcelp_buffer_refresh (struct audio*) ; 
 int /*<<< orphan*/  audqcelp_config_hostpcm (struct audio*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void audqcelp_dsp_event(void *private, unsigned id, uint16_t *msg)
{
	struct audio *audio = private;

	switch (id) {
	case AUDPP_MSG_STATUS_MSG:{
			unsigned status = msg[1];

			switch (status) {
			case AUDPP_DEC_STATUS_SLEEP:
				dprintk("decoder status: sleep \n");
				break;

			case AUDPP_DEC_STATUS_INIT:
				dprintk("decoder status: init \n");
				audpp_cmd_cfg_routing_mode(audio);
				break;

			case AUDPP_DEC_STATUS_CFG:
				dprintk("decoder status: cfg \n");
				break;
			case AUDPP_DEC_STATUS_PLAY:
				dprintk("decoder status: play \n");
				if (audio->pcm_feedback) {
					audqcelp_config_hostpcm(audio);
					audqcelp_buffer_refresh(audio);
				}
				break;
			default:
				pr_err("unknown decoder status \n");
			}
			break;
		}
	case AUDPP_MSG_CFG_MSG:
		if (msg[0] == AUDPP_MSG_ENA_ENA) {
			dprintk("audqcelp_dsp_event: CFG_MSG ENABLE\n");
			auddec_dsp_config(audio, 1);
			audio->out_needed = 0;
			audio->running = 1;
			audpp_set_volume_and_pan(audio->dec_id, audio->volume,
						 0);
			audpp_avsync(audio->dec_id, 22050);
		} else if (msg[0] == AUDPP_MSG_ENA_DIS) {
			dprintk("audqcelp_dsp_event: CFG_MSG DISABLE\n");
			audpp_avsync(audio->dec_id, 0);
			audio->running = 0;
		} else {
			pr_err("audqcelp_dsp_event: CFG_MSG %d?\n", msg[0]);
		}
		break;
	case AUDPP_MSG_ROUTING_ACK:
		dprintk("audqcelp_dsp_event: ROUTING_ACK mode=%d\n", msg[1]);
		audpp_cmd_cfg_adec_params(audio);
		break;
	default:
		pr_err("audqcelp_dsp_event: UNKNOWN (%d)\n", id);
	}

}