#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vc_map {int class; size_t scd_index; int index; int /*<<< orphan*/  flags; struct atm_vcc* tx_vcc; TYPE_2__* scq; } ;
struct idt77252_dev {int /*<<< orphan*/ ** scd2vc; int /*<<< orphan*/  name; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_5__ {int traffic_class; } ;
struct atm_qos {TYPE_1__ txtp; } ;
struct TYPE_6__ {scalar_t__ scd; } ;

/* Variables and functions */
#define  ATM_ABR 133 
#define  ATM_CBR 132 
#define  ATM_UBR 131 
#define  ATM_VBR 130 
 int EBUSY ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  SAR_REG_TCMDQ ; 
#define  SCHED_CBR 129 
#define  SCHED_UBR 128 
 int TCMDQ_START ; 
 int /*<<< orphan*/  VCF_IDLE ; 
 int /*<<< orphan*/  VCF_TX ; 
 TYPE_2__* alloc_scq (struct idt77252_dev*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_scd (struct idt77252_dev*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  free_scq (struct idt77252_dev*,TYPE_2__*) ; 
 scalar_t__ get_free_scd (struct idt77252_dev*,struct vc_map*) ; 
 int idt77252_init_cbr (struct idt77252_dev*,struct vc_map*,struct atm_vcc*,struct atm_qos*) ; 
 int idt77252_init_ubr (struct idt77252_dev*,struct vc_map*,struct atm_vcc*,struct atm_qos*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ set_tct (struct idt77252_dev*,struct vc_map*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idt77252_init_tx(struct idt77252_dev *card, struct vc_map *vc,
		 struct atm_vcc *vcc, struct atm_qos *qos)
{
	int error;

	if (test_bit(VCF_TX, &vc->flags))
		return -EBUSY;

	switch (qos->txtp.traffic_class) {
		case ATM_CBR:
			vc->class = SCHED_CBR;
			break;

		case ATM_UBR:
			vc->class = SCHED_UBR;
			break;

		case ATM_VBR:
		case ATM_ABR:
		default:
			return -EPROTONOSUPPORT;
	}

	vc->scq = alloc_scq(card, vc->class);
	if (!vc->scq) {
		printk("%s: can't get SCQ.\n", card->name);
		return -ENOMEM;
	}

	vc->scq->scd = get_free_scd(card, vc);
	if (vc->scq->scd == 0) {
		printk("%s: no SCD available.\n", card->name);
		free_scq(card, vc->scq);
		return -ENOMEM;
	}

	fill_scd(card, vc->scq, vc->class);

	if (set_tct(card, vc)) {
		printk("%s: class %d not supported.\n",
		       card->name, qos->txtp.traffic_class);

		card->scd2vc[vc->scd_index] = NULL;
		free_scq(card, vc->scq);
		return -EPROTONOSUPPORT;
	}

	switch (vc->class) {
		case SCHED_CBR:
			error = idt77252_init_cbr(card, vc, vcc, qos);
			if (error) {
				card->scd2vc[vc->scd_index] = NULL;
				free_scq(card, vc->scq);
				return error;
			}

			clear_bit(VCF_IDLE, &vc->flags);
			writel(TCMDQ_START | vc->index, SAR_REG_TCMDQ);
			break;

		case SCHED_UBR:
			error = idt77252_init_ubr(card, vc, vcc, qos);
			if (error) {
				card->scd2vc[vc->scd_index] = NULL;
				free_scq(card, vc->scq);
				return error;
			}

			set_bit(VCF_IDLE, &vc->flags);
			break;
	}

	vc->tx_vcc = vcc;
	set_bit(VCF_TX, &vc->flags);
	return 0;
}