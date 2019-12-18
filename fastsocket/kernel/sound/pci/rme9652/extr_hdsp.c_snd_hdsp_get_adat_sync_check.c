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
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct TYPE_4__ {int index; } ;
struct snd_ctl_elem_value {TYPE_3__ value; TYPE_1__ id; } ;
struct hdsp {int io_type; } ;

/* Variables and functions */
#define  Digiface 131 
 int EINVAL ; 
 int EIO ; 
#define  H9632 130 
#define  H9652 129 
#define  Multiface 128 
 int /*<<< orphan*/  hdsp_adat_sync_check (struct hdsp*,int) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 struct hdsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_hdsp_get_adat_sync_check(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	int offset;
	struct hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	offset = ucontrol->id.index - 1;
	snd_BUG_ON(offset < 0);

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		if (offset >= 3)
			return -EINVAL;
		break;
	case Multiface:
	case H9632:
		if (offset >= 1)
			return -EINVAL;
		break;
	default:
		return -EIO;
	}

	ucontrol->value.enumerated.item[0] = hdsp_adat_sync_check(hdsp, offset);
	return 0;
}