#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int version; int /*<<< orphan*/  product; scalar_t__ vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {char* map_name; int timeout; int /*<<< orphan*/  allowed_protos; int /*<<< orphan*/  driver_type; void* scanmask; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct cx88_core* priv; int /*<<< orphan*/  driver_name; TYPE_3__ dev; TYPE_2__ input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  input_name; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; scalar_t__ vendor; int /*<<< orphan*/  subsystem_device; scalar_t__ subsystem_vendor; } ;
struct TYPE_4__ {char* name; } ;
struct cx88_core {int boardnr; struct cx88_IR* ir; TYPE_1__ board; } ;
struct cx88_IR {int mask_keycode; int mask_keyup; int polling; int sampling; int mask_keydown; struct cx88_core* core; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; void* gpio_addr; struct rc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PCI ; 
#define  CX88_BOARD_ADSTECH_DVB_T_PCI 173 
#define  CX88_BOARD_AVERTV_303 172 
#define  CX88_BOARD_AVERTV_STUDIO_303 171 
#define  CX88_BOARD_DNTV_LIVE_DVB_T 170 
#define  CX88_BOARD_DNTV_LIVE_DVB_T_PRO 169 
#define  CX88_BOARD_HAUPPAUGE 168 
#define  CX88_BOARD_HAUPPAUGE_DVB_T1 167 
#define  CX88_BOARD_HAUPPAUGE_HVR1100 166 
#define  CX88_BOARD_HAUPPAUGE_HVR3000 165 
#define  CX88_BOARD_HAUPPAUGE_HVR4000 164 
#define  CX88_BOARD_HAUPPAUGE_HVR4000LITE 163 
#define  CX88_BOARD_HAUPPAUGE_IRONLY 162 
#define  CX88_BOARD_HAUPPAUGE_NOVASE2_S1 161 
#define  CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1 160 
#define  CX88_BOARD_IODATA_GVBCTV7E 159 
#define  CX88_BOARD_KWORLD_DVB_T 158 
#define  CX88_BOARD_KWORLD_DVB_T_CX22702 157 
#define  CX88_BOARD_KWORLD_LTV883 156 
#define  CX88_BOARD_MSI_TVANYWHERE_MASTER 155 
#define  CX88_BOARD_NORWOOD_MICRO 154 
#define  CX88_BOARD_NPGTECH_REALTV_TOP10FM 153 
#define  CX88_BOARD_OMICOM_SS4_PCI 152 
#define  CX88_BOARD_PCHDTV_HD3000 151 
#define  CX88_BOARD_PCHDTV_HD5500 150 
#define  CX88_BOARD_PINNACLE_PCTV_HD_800i 149 
#define  CX88_BOARD_PIXELVIEW_PLAYTV_ULTRA_PRO 148 
#define  CX88_BOARD_POWERCOLOR_REAL_ANGEL 147 
#define  CX88_BOARD_PROF_6200 146 
#define  CX88_BOARD_PROF_7300 145 
#define  CX88_BOARD_PROF_7301 144 
#define  CX88_BOARD_PROLINK_PLAYTVPVR 143 
#define  CX88_BOARD_PROLINK_PV_8000GT 142 
#define  CX88_BOARD_PROLINK_PV_GLOBAL_XTREME 141 
#define  CX88_BOARD_SATTRADE_ST4200 140 
#define  CX88_BOARD_TBS_8910 139 
#define  CX88_BOARD_TBS_8920 138 
#define  CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1 137 
#define  CX88_BOARD_TEVII_S420 136 
#define  CX88_BOARD_TEVII_S460 135 
#define  CX88_BOARD_TWINHAN_VP1027_DVBS 134 
#define  CX88_BOARD_WINFAST2000XP_EXPERT 133 
#define  CX88_BOARD_WINFAST_DTV1000 132 
#define  CX88_BOARD_WINFAST_DTV1800H 131 
#define  CX88_BOARD_WINFAST_DTV2000H 130 
#define  CX88_BOARD_WINFAST_DTV2000H_J 129 
#define  CX88_BOARD_WINFAST_TV2000_XP_GLOBAL 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 void* MO_GP0_IO ; 
 void* MO_GP1_IO ; 
 void* MO_GP2_IO ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_DRIVER_SCANCODE ; 
 char* RC_MAP_ADSTECH_DVB_T_PCI ; 
 char* RC_MAP_AVERTV_303 ; 
 char* RC_MAP_CINERGY_1400 ; 
 char* RC_MAP_DNTV_LIVE_DVBT_PRO ; 
 char* RC_MAP_DNTV_LIVE_DVB_T ; 
 char* RC_MAP_HAUPPAUGE_NEW ; 
 char* RC_MAP_IODATA_BCTV7E ; 
 char* RC_MAP_MSI_TVANYWHERE ; 
 char* RC_MAP_NORWOOD ; 
 char* RC_MAP_NPGTECH ; 
 char* RC_MAP_PINNACLE_PCTV_HD ; 
 char* RC_MAP_PIXELVIEW ; 
 char* RC_MAP_PIXELVIEW_MK12 ; 
 char* RC_MAP_PIXELVIEW_NEW ; 
 char* RC_MAP_POWERCOLOR_REAL_ANGEL ; 
 char* RC_MAP_TBS_NEC ; 
 char* RC_MAP_TEVII_NEC ; 
 char* RC_MAP_TWINHAN_VP1027_DVBS ; 
 char* RC_MAP_WINFAST ; 
 int /*<<< orphan*/  RC_TYPE_NEC ; 
 int /*<<< orphan*/  RC_TYPE_OTHER ; 
 int /*<<< orphan*/  cx88_ir_close ; 
 int /*<<< orphan*/  cx88_ir_open ; 
 int /*<<< orphan*/  kfree (struct cx88_IR*) ; 
 struct cx88_IR* kzalloc (int,int /*<<< orphan*/ ) ; 
 char* pci_name (struct pci_dev*) ; 
 struct rc_dev* rc_allocate_device () ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

int cx88_ir_init(struct cx88_core *core, struct pci_dev *pci)
{
	struct cx88_IR *ir;
	struct rc_dev *dev;
	char *ir_codes = NULL;
	u64 rc_type = RC_TYPE_OTHER;
	int err = -ENOMEM;
	u32 hardware_mask = 0;	/* For devices with a hardware mask, when
				 * used with a full-code IR table
				 */

	ir = kzalloc(sizeof(*ir), GFP_KERNEL);
	dev = rc_allocate_device();
	if (!ir || !dev)
		goto err_out_free;

	ir->dev = dev;

	/* detect & configure */
	switch (core->boardnr) {
	case CX88_BOARD_DNTV_LIVE_DVB_T:
	case CX88_BOARD_KWORLD_DVB_T:
	case CX88_BOARD_KWORLD_DVB_T_CX22702:
		ir_codes = RC_MAP_DNTV_LIVE_DVB_T;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x1f;
		ir->mask_keyup = 0x60;
		ir->polling = 50; /* ms */
		break;
	case CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1:
		ir_codes = RC_MAP_CINERGY_1400;
		ir->sampling = 0xeb04; /* address */
		break;
	case CX88_BOARD_HAUPPAUGE:
	case CX88_BOARD_HAUPPAUGE_DVB_T1:
	case CX88_BOARD_HAUPPAUGE_NOVASE2_S1:
	case CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1:
	case CX88_BOARD_HAUPPAUGE_HVR1100:
	case CX88_BOARD_HAUPPAUGE_HVR3000:
	case CX88_BOARD_HAUPPAUGE_HVR4000:
	case CX88_BOARD_HAUPPAUGE_HVR4000LITE:
	case CX88_BOARD_PCHDTV_HD3000:
	case CX88_BOARD_PCHDTV_HD5500:
	case CX88_BOARD_HAUPPAUGE_IRONLY:
		ir_codes = RC_MAP_HAUPPAUGE_NEW;
		ir->sampling = 1;
		break;
	case CX88_BOARD_WINFAST_DTV2000H:
	case CX88_BOARD_WINFAST_DTV2000H_J:
	case CX88_BOARD_WINFAST_DTV1800H:
		ir_codes = RC_MAP_WINFAST;
		ir->gpio_addr = MO_GP0_IO;
		ir->mask_keycode = 0x8f8;
		ir->mask_keyup = 0x100;
		ir->polling = 50; /* ms */
		break;
	case CX88_BOARD_WINFAST2000XP_EXPERT:
	case CX88_BOARD_WINFAST_DTV1000:
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
		ir_codes = RC_MAP_WINFAST;
		ir->gpio_addr = MO_GP0_IO;
		ir->mask_keycode = 0x8f8;
		ir->mask_keyup = 0x100;
		ir->polling = 1; /* ms */
		break;
	case CX88_BOARD_IODATA_GVBCTV7E:
		ir_codes = RC_MAP_IODATA_BCTV7E;
		ir->gpio_addr = MO_GP0_IO;
		ir->mask_keycode = 0xfd;
		ir->mask_keydown = 0x02;
		ir->polling = 5; /* ms */
		break;
	case CX88_BOARD_PROLINK_PLAYTVPVR:
	case CX88_BOARD_PIXELVIEW_PLAYTV_ULTRA_PRO:
		/*
		 * It seems that this hardware is paired with NEC extended
		 * address 0x866b. So, unfortunately, its usage with other
		 * IR's with different address won't work. Still, there are
		 * other IR's from the same manufacturer that works, like the
		 * 002-T mini RC, provided with newer PV hardware
		 */
		ir_codes = RC_MAP_PIXELVIEW_MK12;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keyup = 0x80;
		ir->polling = 10; /* ms */
		hardware_mask = 0x3f;	/* Hardware returns only 6 bits from command part */
		break;
	case CX88_BOARD_PROLINK_PV_8000GT:
	case CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
		ir_codes = RC_MAP_PIXELVIEW_NEW;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x3f;
		ir->mask_keyup = 0x80;
		ir->polling = 1; /* ms */
		break;
	case CX88_BOARD_KWORLD_LTV883:
		ir_codes = RC_MAP_PIXELVIEW;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x1f;
		ir->mask_keyup = 0x60;
		ir->polling = 1; /* ms */
		break;
	case CX88_BOARD_ADSTECH_DVB_T_PCI:
		ir_codes = RC_MAP_ADSTECH_DVB_T_PCI;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0xbf;
		ir->mask_keyup = 0x40;
		ir->polling = 50; /* ms */
		break;
	case CX88_BOARD_MSI_TVANYWHERE_MASTER:
		ir_codes = RC_MAP_MSI_TVANYWHERE;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x1f;
		ir->mask_keyup = 0x40;
		ir->polling = 1; /* ms */
		break;
	case CX88_BOARD_AVERTV_303:
	case CX88_BOARD_AVERTV_STUDIO_303:
		ir_codes         = RC_MAP_AVERTV_303;
		ir->gpio_addr    = MO_GP2_IO;
		ir->mask_keycode = 0xfb;
		ir->mask_keydown = 0x02;
		ir->polling      = 50; /* ms */
		break;
	case CX88_BOARD_OMICOM_SS4_PCI:
	case CX88_BOARD_SATTRADE_ST4200:
	case CX88_BOARD_TBS_8920:
	case CX88_BOARD_TBS_8910:
	case CX88_BOARD_PROF_7300:
	case CX88_BOARD_PROF_7301:
	case CX88_BOARD_PROF_6200:
		ir_codes = RC_MAP_TBS_NEC;
		ir->sampling = 0xff00; /* address */
		break;
	case CX88_BOARD_TEVII_S460:
	case CX88_BOARD_TEVII_S420:
		ir_codes = RC_MAP_TEVII_NEC;
		ir->sampling = 0xff00; /* address */
		break;
	case CX88_BOARD_DNTV_LIVE_DVB_T_PRO:
		ir_codes         = RC_MAP_DNTV_LIVE_DVBT_PRO;
		ir->sampling     = 0xff00; /* address */
		break;
	case CX88_BOARD_NORWOOD_MICRO:
		ir_codes         = RC_MAP_NORWOOD;
		ir->gpio_addr    = MO_GP1_IO;
		ir->mask_keycode = 0x0e;
		ir->mask_keyup   = 0x80;
		ir->polling      = 50; /* ms */
		break;
	case CX88_BOARD_NPGTECH_REALTV_TOP10FM:
		ir_codes         = RC_MAP_NPGTECH;
		ir->gpio_addr    = MO_GP0_IO;
		ir->mask_keycode = 0xfa;
		ir->polling      = 50; /* ms */
		break;
	case CX88_BOARD_PINNACLE_PCTV_HD_800i:
		ir_codes         = RC_MAP_PINNACLE_PCTV_HD;
		ir->sampling     = 1;
		break;
	case CX88_BOARD_POWERCOLOR_REAL_ANGEL:
		ir_codes         = RC_MAP_POWERCOLOR_REAL_ANGEL;
		ir->gpio_addr    = MO_GP2_IO;
		ir->mask_keycode = 0x7e;
		ir->polling      = 100; /* ms */
		break;
	case CX88_BOARD_TWINHAN_VP1027_DVBS:
		ir_codes         = RC_MAP_TWINHAN_VP1027_DVBS;
		rc_type          = RC_TYPE_NEC;
		ir->sampling     = 0xff00; /* address */
		break;
	}

	if (!ir_codes) {
		err = -ENODEV;
		goto err_out_free;
	}

	/*
	 * The usage of mask_keycode were very convenient, due to several
	 * reasons. Among others, the scancode tables were using the scancode
	 * as the index elements. So, the less bits it was used, the smaller
	 * the table were stored. After the input changes, the better is to use
	 * the full scancodes, since it allows replacing the IR remote by
	 * another one. Unfortunately, there are still some hardware, like
	 * Pixelview Ultra Pro, where only part of the scancode is sent via
	 * GPIO. So, there's no way to get the full scancode. Due to that,
	 * hardware_mask were introduced here: it represents those hardware
	 * that has such limits.
	 */
	if (hardware_mask && !ir->mask_keycode)
		ir->mask_keycode = hardware_mask;

	/* init input device */
	snprintf(ir->name, sizeof(ir->name), "cx88 IR (%s)", core->board.name);
	snprintf(ir->phys, sizeof(ir->phys), "pci-%s/ir0", pci_name(pci));

	dev->input_name = ir->name;
	dev->input_phys = ir->phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.version = 1;
	if (pci->subsystem_vendor) {
		dev->input_id.vendor = pci->subsystem_vendor;
		dev->input_id.product = pci->subsystem_device;
	} else {
		dev->input_id.vendor = pci->vendor;
		dev->input_id.product = pci->device;
	}
	dev->dev.parent = &pci->dev;
	dev->map_name = ir_codes;
	dev->driver_name = MODULE_NAME;
	dev->priv = core;
	dev->open = cx88_ir_open;
	dev->close = cx88_ir_close;
	dev->scanmask = hardware_mask;

	if (ir->sampling) {
		dev->driver_type = RC_DRIVER_IR_RAW;
		dev->timeout = 10 * 1000 * 1000; /* 10 ms */
	} else {
		dev->driver_type = RC_DRIVER_SCANCODE;
		dev->allowed_protos = rc_type;
	}

	ir->core = core;
	core->ir = ir;

	/* all done */
	err = rc_register_device(dev);
	if (err)
		goto err_out_free;

	return 0;

err_out_free:
	rc_free_device(dev);
	core->ir = NULL;
	kfree(ir);
	return err;
}