#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct saa7146_pci_extension_data {struct budget_info* ext_priv; } ;
struct saa7146_dev {TYPE_2__* pci; int /*<<< orphan*/  name; } ;
struct module {int dummy; } ;
struct budget_info {int type; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  proposed_mac; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct budget {int buffer_width; int buffer_height; int buffer_size; int buffer_warning_threshold; TYPE_7__ dvb_adapter; TYPE_1__ i2c_adap; int /*<<< orphan*/  pt; int /*<<< orphan*/ * grabbing; int /*<<< orphan*/  vpe_tasklet; struct budget_info* card; int /*<<< orphan*/  debilock; int /*<<< orphan*/  feedlock; int /*<<< orphan*/  video_port; struct saa7146_dev* dev; int /*<<< orphan*/  buffer_warning_time; scalar_t__ buffer_warnings; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  BUDGET_CIN1200C 134 
#define  BUDGET_CIN1200C_MK3 133 
#define  BUDGET_FS_ACTIVY 132 
#define  BUDGET_KNC1C 131 
#define  BUDGET_KNC1CP 130 
#define  BUDGET_KNC1CP_MK3 129 
#define  BUDGET_KNC1C_MK3 128 
 int /*<<< orphan*/  BUDGET_VIDEO_PORTA ; 
 int /*<<< orphan*/  BUDGET_VIDEO_PORTB ; 
 int /*<<< orphan*/  DD1_INIT ; 
 int /*<<< orphan*/  DD1_STREAM_B ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int MASK_09 ; 
 int MASK_10 ; 
 int MASK_25 ; 
 int MASK_26 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  PCI_BT_V1 ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  SAA7146_I2C_BUS_BIT_RATE_120 ; 
 int TS_HEIGHT_MASK ; 
 int TS_HEIGHT_MASK_ACTIVY ; 
 int TS_HEIGHT_MASK_DVBC ; 
 int TS_MAX_BUFSIZE_K ; 
 int TS_MAX_BUFSIZE_K_ACTIVY ; 
 int TS_MAX_BUFSIZE_K_DVBC ; 
 int TS_MIN_BUFSIZE_K ; 
 int TS_WIDTH ; 
 int TS_WIDTH_ACTIVY ; 
 int TS_WIDTH_DVBC ; 
 int budget_register (struct budget*) ; 
 int dma_buffer_size ; 
 int /*<<< orphan*/  dprintk (int,char*,struct saa7146_dev*,...) ; 
 int dvb_register_adapter (TYPE_7__*,int /*<<< orphan*/ ,struct module*,int /*<<< orphan*/ *,short*) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (TYPE_7__*) ; 
 scalar_t__ i2c_add_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct budget*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7146_i2c_adapter_prepare (struct saa7146_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_vfree_destroy_pgtable (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * saa7146_vmalloc_build_pgtable (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ttpci_eeprom_parse_mac (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpeirq ; 

int ttpci_budget_init(struct budget *budget, struct saa7146_dev *dev,
		      struct saa7146_pci_extension_data *info,
		      struct module *owner, short *adapter_nums)
{
	int ret = 0;
	struct budget_info *bi = info->ext_priv;
	int max_bufsize;
	int height_mask;

	memset(budget, 0, sizeof(struct budget));

	dprintk(2, "dev: %p, budget: %p\n", dev, budget);

	budget->card = bi;
	budget->dev = (struct saa7146_dev *) dev;

	switch(budget->card->type) {
	case BUDGET_FS_ACTIVY:
		budget->buffer_width = TS_WIDTH_ACTIVY;
		max_bufsize = TS_MAX_BUFSIZE_K_ACTIVY;
		height_mask = TS_HEIGHT_MASK_ACTIVY;
		break;

	case BUDGET_KNC1C:
	case BUDGET_KNC1CP:
	case BUDGET_CIN1200C:
	case BUDGET_KNC1C_MK3:
	case BUDGET_KNC1CP_MK3:
	case BUDGET_CIN1200C_MK3:
		budget->buffer_width = TS_WIDTH_DVBC;
		max_bufsize = TS_MAX_BUFSIZE_K_DVBC;
		height_mask = TS_HEIGHT_MASK_DVBC;
		break;

	default:
		budget->buffer_width = TS_WIDTH;
		max_bufsize = TS_MAX_BUFSIZE_K;
		height_mask = TS_HEIGHT_MASK;
	}

	if (dma_buffer_size < TS_MIN_BUFSIZE_K)
		dma_buffer_size = TS_MIN_BUFSIZE_K;
	else if (dma_buffer_size > max_bufsize)
		dma_buffer_size = max_bufsize;

	budget->buffer_height = dma_buffer_size * 1024 / budget->buffer_width;
	if (budget->buffer_height > 0xfff) {
		budget->buffer_height /= 2;
		budget->buffer_height &= height_mask;
		budget->buffer_size = 2 * budget->buffer_height * budget->buffer_width;
	} else {
		budget->buffer_height &= height_mask;
		budget->buffer_size = budget->buffer_height * budget->buffer_width;
	}
	budget->buffer_warning_threshold = budget->buffer_size * 80/100;
	budget->buffer_warnings = 0;
	budget->buffer_warning_time = jiffies;

	dprintk(2, "%s: buffer type = %s, width = %d, height = %d\n",
		budget->dev->name,
		budget->buffer_size > budget->buffer_width * budget->buffer_height ? "odd/even" : "single",
		budget->buffer_width, budget->buffer_height);
	printk("%s: dma buffer size %u\n", budget->dev->name, budget->buffer_size);

	ret = dvb_register_adapter(&budget->dvb_adapter, budget->card->name,
				   owner, &budget->dev->pci->dev, adapter_nums);
	if (ret < 0)
		return ret;

	/* set dd1 stream a & b */
	saa7146_write(dev, DD1_STREAM_B, 0x00000000);
	saa7146_write(dev, MC2, (MASK_09 | MASK_25));
	saa7146_write(dev, MC2, (MASK_10 | MASK_26));
	saa7146_write(dev, DD1_INIT, 0x02000000);
	saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	if (bi->type != BUDGET_FS_ACTIVY)
		budget->video_port = BUDGET_VIDEO_PORTB;
	else
		budget->video_port = BUDGET_VIDEO_PORTA;
	spin_lock_init(&budget->feedlock);
	spin_lock_init(&budget->debilock);

	/* the Siemens DVB needs this if you want to have the i2c chips
	   get recognized before the main driver is loaded */
	if (bi->type != BUDGET_FS_ACTIVY)
		saa7146_write(dev, GPIO_CTRL, 0x500000);	/* GPIO 3 = 1 */

	strlcpy(budget->i2c_adap.name, budget->card->name, sizeof(budget->i2c_adap.name));

	saa7146_i2c_adapter_prepare(dev, &budget->i2c_adap, SAA7146_I2C_BUS_BIT_RATE_120);
	strcpy(budget->i2c_adap.name, budget->card->name);

	if (i2c_add_adapter(&budget->i2c_adap) < 0) {
		ret = -ENOMEM;
		goto err_dvb_unregister;
	}

	ttpci_eeprom_parse_mac(&budget->i2c_adap, budget->dvb_adapter.proposed_mac);

	budget->grabbing = saa7146_vmalloc_build_pgtable(dev->pci, budget->buffer_size, &budget->pt);
	if (NULL == budget->grabbing) {
		ret = -ENOMEM;
		goto err_del_i2c;
	}

	saa7146_write(dev, PCI_BT_V1, 0x001c0000);
	/* upload all */
	saa7146_write(dev, GPIO_CTRL, 0x000000);

	tasklet_init(&budget->vpe_tasklet, vpeirq, (unsigned long) budget);

	/* frontend power on */
	if (bi->type != BUDGET_FS_ACTIVY)
		saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	if ((ret = budget_register(budget)) == 0)
		return 0; /* Everything OK */

	/* An error occurred, cleanup resources */
	saa7146_vfree_destroy_pgtable(dev->pci, budget->grabbing, &budget->pt);

err_del_i2c:
	i2c_del_adapter(&budget->i2c_adap);

err_dvb_unregister:
	dvb_unregister_adapter(&budget->dvb_adapter);

	return ret;
}