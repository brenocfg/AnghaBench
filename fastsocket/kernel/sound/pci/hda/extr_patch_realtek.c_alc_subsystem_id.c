#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {int subsystem_id; int vendor_id; TYPE_3__* bus; struct alc_spec* spec; } ;
struct TYPE_9__ {scalar_t__ line_out_type; int /*<<< orphan*/ * hp_pins; int /*<<< orphan*/  line_outs; scalar_t__* line_out_pins; } ;
struct TYPE_10__ {TYPE_4__ autocfg; } ;
struct TYPE_6__ {unsigned int sku_cfg; scalar_t__ fixup; } ;
struct alc_spec {TYPE_5__ gen; int /*<<< orphan*/  init_amp; TYPE_1__ cdefine; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_8__ {TYPE_2__* pci; } ;
struct TYPE_7__ {unsigned int subsystem_device; } ;

/* Variables and functions */
 unsigned int ALC_FIXUP_SKU_IGNORE ; 
 int /*<<< orphan*/  ALC_INIT_DEFAULT ; 
 int /*<<< orphan*/  ALC_INIT_GPIO1 ; 
 int /*<<< orphan*/  ALC_INIT_GPIO2 ; 
 int /*<<< orphan*/  ALC_INIT_GPIO3 ; 
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ found_in_nid_list (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  snd_printd (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int alc_subsystem_id(struct hda_codec *codec,
			    hda_nid_t porta, hda_nid_t porte,
			    hda_nid_t portd, hda_nid_t porti)
{
	unsigned int ass, tmp, i;
	unsigned nid;
	struct alc_spec *spec = codec->spec;

	if (spec->cdefine.fixup) {
		ass = spec->cdefine.sku_cfg;
		if (ass == ALC_FIXUP_SKU_IGNORE)
			return 0;
		goto do_sku;
	}

	ass = codec->subsystem_id & 0xffff;
	if ((ass != codec->bus->pci->subsystem_device) && (ass & 1))
		goto do_sku;

	/* invalid SSID, check the special NID pin defcfg instead */
	/*
	 * 31~30	: port connectivity
	 * 29~21	: reserve
	 * 20		: PCBEEP input
	 * 19~16	: Check sum (15:1)
	 * 15~1		: Custom
	 * 0		: override
	*/
	nid = 0x1d;
	if (codec->vendor_id == 0x10ec0260)
		nid = 0x17;
	ass = snd_hda_codec_get_pincfg(codec, nid);
	snd_printd("realtek: No valid SSID, "
		   "checking pincfg 0x%08x for NID 0x%x\n",
		   ass, nid);
	if (!(ass & 1))
		return 0;
	if ((ass >> 30) != 1)	/* no physical connection */
		return 0;

	/* check sum */
	tmp = 0;
	for (i = 1; i < 16; i++) {
		if ((ass >> i) & 1)
			tmp++;
	}
	if (((ass >> 16) & 0xf) != tmp)
		return 0;
do_sku:
	snd_printd("realtek: Enabling init ASM_ID=0x%04x CODEC_ID=%08x\n",
		   ass & 0xffff, codec->vendor_id);
	/*
	 * 0 : override
	 * 1 :	Swap Jack
	 * 2 : 0 --> Desktop, 1 --> Laptop
	 * 3~5 : External Amplifier control
	 * 7~6 : Reserved
	*/
	tmp = (ass & 0x38) >> 3;	/* external Amp control */
	switch (tmp) {
	case 1:
		spec->init_amp = ALC_INIT_GPIO1;
		break;
	case 3:
		spec->init_amp = ALC_INIT_GPIO2;
		break;
	case 7:
		spec->init_amp = ALC_INIT_GPIO3;
		break;
	case 5:
	default:
		spec->init_amp = ALC_INIT_DEFAULT;
		break;
	}

	/* is laptop or Desktop and enable the function "Mute internal speaker
	 * when the external headphone out jack is plugged"
	 */
	if (!(ass & 0x8000))
		return 1;
	/*
	 * 10~8 : Jack location
	 * 12~11: Headphone out -> 00: PortA, 01: PortE, 02: PortD, 03: Resvered
	 * 14~13: Resvered
	 * 15   : 1 --> enable the function "Mute internal speaker
	 *	        when the external headphone out jack is plugged"
	 */
	if (!spec->gen.autocfg.hp_pins[0] &&
	    !(spec->gen.autocfg.line_out_pins[0] &&
	      spec->gen.autocfg.line_out_type == AUTO_PIN_HP_OUT)) {
		hda_nid_t nid;
		tmp = (ass >> 11) & 0x3;	/* HP to chassis */
		if (tmp == 0)
			nid = porta;
		else if (tmp == 1)
			nid = porte;
		else if (tmp == 2)
			nid = portd;
		else if (tmp == 3)
			nid = porti;
		else
			return 1;
		if (found_in_nid_list(nid, spec->gen.autocfg.line_out_pins,
				      spec->gen.autocfg.line_outs))
			return 1;
		spec->gen.autocfg.hp_pins[0] = nid;
	}
	return 1;
}