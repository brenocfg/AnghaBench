#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct ca0132_spec* spec; } ;
struct TYPE_2__ {int* dac_nids; int num_dacs; int max_channels; int dig_out_nid; } ;
struct auto_pin_cfg {int* dig_out_pins; int dig_outs; int dig_in_pin; void* dig_in_type; void** dig_out_type; } ;
struct ca0132_spec {int* dacs; int num_outputs; int* out_pins; int shared_out_nid; int num_inputs; int* adcs; int shared_mic_nid; int* input_pins; int dig_out; int dig_in; TYPE_1__ multiout; struct auto_pin_cfg autocfg; } ;

/* Variables and functions */
 void* HDA_PCM_TYPE_SPDIF ; 

__attribute__((used)) static void ca0132_config(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;

	spec->dacs[0] = 0x2;
	spec->dacs[1] = 0x3;
	spec->dacs[2] = 0x4;

	spec->multiout.dac_nids = spec->dacs;
	spec->multiout.num_dacs = 3;
	spec->multiout.max_channels = 2;

	spec->num_outputs = 2;
	spec->out_pins[0] = 0x0b; /* speaker out */
	spec->out_pins[1] = 0x10; /* headphone out */
	spec->shared_out_nid = 0x2;

	spec->num_inputs = 3;
	spec->adcs[0] = 0x7; /* digital mic / analog mic1 */
	spec->adcs[1] = 0x8; /* analog mic2 */
	spec->adcs[2] = 0xa; /* what u hear */
	spec->shared_mic_nid = 0x7;

	spec->input_pins[0] = 0x12;
	spec->input_pins[1] = 0x11;
	spec->input_pins[2] = 0x13;

	/* SPDIF I/O */
	spec->dig_out = 0x05;
	spec->multiout.dig_out_nid = spec->dig_out;
	cfg->dig_out_pins[0] = 0x0c;
	cfg->dig_outs = 1;
	cfg->dig_out_type[0] = HDA_PCM_TYPE_SPDIF;
	spec->dig_in = 0x09;
	cfg->dig_in_pin = 0x0e;
	cfg->dig_in_type = HDA_PCM_TYPE_SPDIF;
}