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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdmi_spec {int dummy; } ;
struct hdmi_eld {scalar_t__ eld_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  eld_buffer; scalar_t__ eld_valid; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct TYPE_6__ {struct hdmi_eld sink_eld; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_3__* get_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int hdmi_eld_ctl_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_eld *eld;
	int pin_idx;

	pin_idx = kcontrol->private_value;
	eld = &get_pin(spec, pin_idx)->sink_eld;

	mutex_lock(&eld->lock);
	if (eld->eld_size > ARRAY_SIZE(ucontrol->value.bytes.data)) {
		mutex_unlock(&eld->lock);
		snd_BUG();
		return -EINVAL;
	}

	memset(ucontrol->value.bytes.data, 0,
	       ARRAY_SIZE(ucontrol->value.bytes.data));
	if (eld->eld_valid)
		memcpy(ucontrol->value.bytes.data, eld->eld_buffer,
		       eld->eld_size);
	mutex_unlock(&eld->lock);

	return 0;
}