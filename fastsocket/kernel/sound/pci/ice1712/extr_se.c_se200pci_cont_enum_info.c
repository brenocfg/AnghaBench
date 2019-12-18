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
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/ * member; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 TYPE_3__* se200pci_cont ; 
 int se200pci_get_enum_count (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int se200pci_cont_enum_info(struct snd_kcontrol *kc,
				   struct snd_ctl_elem_info *uinfo)
{
	int n, c;

	n = kc->private_value;
	c = se200pci_get_enum_count(n);
	if (!c)
		return -EINVAL;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = c;
	if (uinfo->value.enumerated.item >= c)
		uinfo->value.enumerated.item = c - 1;
	strcpy(uinfo->value.enumerated.name,
	       se200pci_cont[n].member[uinfo->value.enumerated.item]);
	return 0;
}