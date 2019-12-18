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
struct ics5342_info {int dummy; } ;
struct dac_info {void* data; int /*<<< orphan*/  dac_write_regs; int /*<<< orphan*/  dac_read_regs; int /*<<< orphan*/ * dacops; } ;
typedef  int /*<<< orphan*/  dac_write_regs_t ;
typedef  int /*<<< orphan*/  dac_read_regs_t ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 TYPE_1__* DAC_PAR (struct dac_info*) ; 
 int /*<<< orphan*/  DAC_PSEUDO8_8 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ics5342_ops ; 
 struct dac_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dac_info * ics5342_init(dac_read_regs_t drr, dac_write_regs_t dwr, void *data)
{
	struct dac_info *info = kzalloc(sizeof(struct ics5342_info), GFP_KERNEL);

	if (! info)
		return NULL;

	info->dacops = &ics5342_ops;
	info->dac_read_regs = drr;
	info->dac_write_regs = dwr;
	info->data = data;
	DAC_PAR(info)->mode = DAC_PSEUDO8_8; /* estimation */
	return info;
}