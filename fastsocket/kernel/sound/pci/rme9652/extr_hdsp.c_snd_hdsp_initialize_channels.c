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
struct hdsp {int io_type; char* card_name; int /*<<< orphan*/  ds_out_channels; int /*<<< orphan*/  ds_in_channels; int /*<<< orphan*/  ss_out_channels; int /*<<< orphan*/  ss_in_channels; int /*<<< orphan*/  qs_out_channels; int /*<<< orphan*/  qs_in_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGIFACE_DS_CHANNELS ; 
 int /*<<< orphan*/  DIGIFACE_SS_CHANNELS ; 
#define  Digiface 131 
#define  H9632 130 
 int /*<<< orphan*/  H9632_DS_CHANNELS ; 
 int /*<<< orphan*/  H9632_QS_CHANNELS ; 
 int /*<<< orphan*/  H9632_SS_CHANNELS ; 
#define  H9652 129 
 int /*<<< orphan*/  H9652_DS_CHANNELS ; 
 int /*<<< orphan*/  H9652_SS_CHANNELS ; 
 int HDSP_AEBI ; 
 int HDSP_AEBO ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int /*<<< orphan*/  MULTIFACE_DS_CHANNELS ; 
 int /*<<< orphan*/  MULTIFACE_SS_CHANNELS ; 
#define  Multiface 128 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_hdsp_initialize_channels(struct hdsp *hdsp)
{
	int status, aebi_channels, aebo_channels;

	switch (hdsp->io_type) {
	case Digiface:
		hdsp->card_name = "RME Hammerfall DSP + Digiface";
		hdsp->ss_in_channels = hdsp->ss_out_channels = DIGIFACE_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = DIGIFACE_DS_CHANNELS;
		break;

	case H9652:
		hdsp->card_name = "RME Hammerfall HDSP 9652";
		hdsp->ss_in_channels = hdsp->ss_out_channels = H9652_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = H9652_DS_CHANNELS;
		break;

	case H9632:
		status = hdsp_read(hdsp, HDSP_statusRegister);
		/* HDSP_AEBx bits are low when AEB are connected */
		aebi_channels = (status & HDSP_AEBI) ? 0 : 4;
		aebo_channels = (status & HDSP_AEBO) ? 0 : 4;
		hdsp->card_name = "RME Hammerfall HDSP 9632";
		hdsp->ss_in_channels = H9632_SS_CHANNELS+aebi_channels;
		hdsp->ds_in_channels = H9632_DS_CHANNELS+aebi_channels;
		hdsp->qs_in_channels = H9632_QS_CHANNELS+aebi_channels;
		hdsp->ss_out_channels = H9632_SS_CHANNELS+aebo_channels;
		hdsp->ds_out_channels = H9632_DS_CHANNELS+aebo_channels;
		hdsp->qs_out_channels = H9632_QS_CHANNELS+aebo_channels;
		break;

	case Multiface:
		hdsp->card_name = "RME Hammerfall DSP + Multiface";
		hdsp->ss_in_channels = hdsp->ss_out_channels = MULTIFACE_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = MULTIFACE_DS_CHANNELS;
		break;

	default:
 		/* should never get here */
		break;
	}
}