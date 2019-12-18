#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct omapfb_platform_data {struct blizzard_platform_data* ctrl_platform_data; } ;
struct omapfb_mem_desc {int dummy; } ;
struct omapfb_device {TYPE_5__* dev; TYPE_4__* panel; TYPE_1__* int_ctrl; TYPE_2__* ext_if; } ;
struct blizzard_platform_data {unsigned long (* get_clock_rate ) (TYPE_5__*) ;scalar_t__ te_connected; int /*<<< orphan*/  (* power_up ) (TYPE_5__*) ;int /*<<< orphan*/  (* power_down ) (TYPE_5__*) ;} ;
struct TYPE_21__ {scalar_t__ data; int /*<<< orphan*/  function; } ;
struct TYPE_20__ {struct omapfb_platform_data* platform_data; } ;
struct TYPE_19__ {int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; } ;
struct TYPE_18__ {scalar_t__ format; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; scalar_t__ out_x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_17__ {int (* init ) (struct omapfb_device*) ;int /*<<< orphan*/  (* cleanup ) () ;int /*<<< orphan*/  max_transmit_size; } ;
struct TYPE_16__ {int (* init ) (struct omapfb_device*,int,struct omapfb_mem_desc*) ;int /*<<< orphan*/  (* cleanup ) () ;int /*<<< orphan*/  mmap; int /*<<< orphan*/  setup_mem; int /*<<< orphan*/  get_color_key; int /*<<< orphan*/  set_color_key; } ;
struct TYPE_15__ {int /*<<< orphan*/  entry; } ;
struct TYPE_14__ {int te_connected; TYPE_1__* int_ctrl; TYPE_2__* extif; int /*<<< orphan*/  (* power_down ) (TYPE_5__*) ;int /*<<< orphan*/  req_sema; int /*<<< orphan*/  free_req_list; TYPE_12__* req_pool; int /*<<< orphan*/  pending_req_list; TYPE_8__ auto_update_timer; int /*<<< orphan*/  screen_height; int /*<<< orphan*/  screen_width; TYPE_3__ auto_update_window; int /*<<< orphan*/  update_mode; int /*<<< orphan*/  max_transmit_size; int /*<<< orphan*/  version; int /*<<< orphan*/  reg_timings; int /*<<< orphan*/  (* power_up ) (TYPE_5__*) ;int /*<<< orphan*/  req_lock; struct omapfb_device* fbdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  mmap; int /*<<< orphan*/  setup_mem; int /*<<< orphan*/  get_color_key; int /*<<< orphan*/  set_color_key; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_12__*) ; 
 int /*<<< orphan*/  BLIZZARD_CONFIG ; 
 int /*<<< orphan*/  BLIZZARD_PLL_DIV ; 
 int /*<<< orphan*/  BLIZZARD_REV_CODE ; 
 int /*<<< orphan*/  BLIZZARD_VERSION_S1D13744 ; 
 int /*<<< orphan*/  BLIZZARD_VERSION_S1D13745 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQ_REQ_POOL_SIZE ; 
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 TYPE_11__ blizzard ; 
 TYPE_10__ blizzard_ctrl ; 
 int blizzard_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_update_window_auto ; 
 int /*<<< orphan*/  calc_blizzard_clk_rates (unsigned long,unsigned long*,unsigned long*) ; 
 int calc_extif_timings (unsigned long,int*) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  init_timer (TYPE_8__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_extif_timings (int /*<<< orphan*/ *) ; 
 int setup_tearsync (unsigned long,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct omapfb_device*,int,struct omapfb_mem_desc*) ; 
 int stub2 (struct omapfb_device*) ; 
 unsigned long stub3 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub6 () ; 
 int /*<<< orphan*/  stub7 () ; 

__attribute__((used)) static int blizzard_init(struct omapfb_device *fbdev, int ext_mode,
			 struct omapfb_mem_desc *req_vram)
{
	int r = 0, i;
	u8 rev, conf;
	unsigned long ext_clk;
	int extif_div;
	unsigned long sys_clk, pix_clk;
	struct omapfb_platform_data *omapfb_conf;
	struct blizzard_platform_data *ctrl_conf;

	blizzard.fbdev = fbdev;

	BUG_ON(!fbdev->ext_if || !fbdev->int_ctrl);

	blizzard.fbdev = fbdev;
	blizzard.extif = fbdev->ext_if;
	blizzard.int_ctrl = fbdev->int_ctrl;

	omapfb_conf = fbdev->dev->platform_data;
	ctrl_conf = omapfb_conf->ctrl_platform_data;
	if (ctrl_conf == NULL || ctrl_conf->get_clock_rate == NULL) {
		dev_err(fbdev->dev, "s1d1374x: missing platform data\n");
		r = -ENOENT;
		goto err1;
	}

	blizzard.power_down = ctrl_conf->power_down;
	blizzard.power_up = ctrl_conf->power_up;

	spin_lock_init(&blizzard.req_lock);

	if ((r = blizzard.int_ctrl->init(fbdev, 1, req_vram)) < 0)
		goto err1;

	if ((r = blizzard.extif->init(fbdev)) < 0)
		goto err2;

	blizzard_ctrl.set_color_key = blizzard.int_ctrl->set_color_key;
	blizzard_ctrl.get_color_key = blizzard.int_ctrl->get_color_key;
	blizzard_ctrl.setup_mem = blizzard.int_ctrl->setup_mem;
	blizzard_ctrl.mmap = blizzard.int_ctrl->mmap;

	ext_clk = ctrl_conf->get_clock_rate(fbdev->dev);
	if ((r = calc_extif_timings(ext_clk, &extif_div)) < 0)
		goto err3;

	set_extif_timings(&blizzard.reg_timings);

	if (blizzard.power_up != NULL)
		blizzard.power_up(fbdev->dev);

	calc_blizzard_clk_rates(ext_clk, &sys_clk, &pix_clk);

	if ((r = calc_extif_timings(sys_clk, &extif_div)) < 0)
		goto err3;
	set_extif_timings(&blizzard.reg_timings);

	if (!(blizzard_read_reg(BLIZZARD_PLL_DIV) & 0x80)) {
		dev_err(fbdev->dev,
			"controller not initialized by the bootloader\n");
		r = -ENODEV;
		goto err3;
	}

	if (ctrl_conf->te_connected) {
		if ((r = setup_tearsync(pix_clk, extif_div)) < 0)
			goto err3;
		blizzard.te_connected = 1;
	}

	rev = blizzard_read_reg(BLIZZARD_REV_CODE);
	conf = blizzard_read_reg(BLIZZARD_CONFIG);

	switch (rev & 0xfc) {
	case 0x9c:
		blizzard.version = BLIZZARD_VERSION_S1D13744;
		pr_info("omapfb: s1d13744 LCD controller rev %d "
			"initialized (CNF pins %x)\n", rev & 0x03, conf & 0x07);
		break;
	case 0xa4:
		blizzard.version = BLIZZARD_VERSION_S1D13745;
		pr_info("omapfb: s1d13745 LCD controller rev %d "
			"initialized (CNF pins %x)\n", rev & 0x03, conf & 0x07);
		break;
	default:
		dev_err(fbdev->dev, "invalid s1d1374x revision %02x\n",
			rev);
		r = -ENODEV;
		goto err3;
	}

	blizzard.max_transmit_size = blizzard.extif->max_transmit_size;

	blizzard.update_mode = OMAPFB_UPDATE_DISABLED;

	blizzard.auto_update_window.x = 0;
	blizzard.auto_update_window.y = 0;
	blizzard.auto_update_window.width = fbdev->panel->x_res;
	blizzard.auto_update_window.height = fbdev->panel->y_res;
	blizzard.auto_update_window.out_x = 0;
	blizzard.auto_update_window.out_x = 0;
	blizzard.auto_update_window.out_width = fbdev->panel->x_res;
	blizzard.auto_update_window.out_height = fbdev->panel->y_res;
	blizzard.auto_update_window.format = 0;

	blizzard.screen_width = fbdev->panel->x_res;
	blizzard.screen_height = fbdev->panel->y_res;

	init_timer(&blizzard.auto_update_timer);
	blizzard.auto_update_timer.function = blizzard_update_window_auto;
	blizzard.auto_update_timer.data = 0;

	INIT_LIST_HEAD(&blizzard.free_req_list);
	INIT_LIST_HEAD(&blizzard.pending_req_list);
	for (i = 0; i < ARRAY_SIZE(blizzard.req_pool); i++)
		list_add(&blizzard.req_pool[i].entry, &blizzard.free_req_list);
	BUG_ON(i <= IRQ_REQ_POOL_SIZE);
	sema_init(&blizzard.req_sema, i - IRQ_REQ_POOL_SIZE);

	return 0;
err3:
	if (blizzard.power_down != NULL)
		blizzard.power_down(fbdev->dev);
	blizzard.extif->cleanup();
err2:
	blizzard.int_ctrl->cleanup();
err1:
	return r;
}