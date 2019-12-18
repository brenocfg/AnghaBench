#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  map_slave_func_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  check_slave_present ; 
 int /*<<< orphan*/  init_slave_0dB ; 
 int /*<<< orphan*/  init_slave_unmute ; 
 int map_slaves (struct hda_codec*,char const* const*,char const*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  put_kctl_with_value (struct snd_kcontrol*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_ctl_add_slave ; 
 struct snd_kcontrol* snd_ctl_make_virtual_master (char*,unsigned int*) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_printdd (char*,char*) ; 

int __snd_hda_add_vmaster(struct hda_codec *codec, char *name,
			unsigned int *tlv, const char * const *slaves,
			  const char *suffix, bool init_slave_vol,
			  struct snd_kcontrol **ctl_ret)
{
	struct snd_kcontrol *kctl;
	int err;

	if (ctl_ret)
		*ctl_ret = NULL;

	err = map_slaves(codec, slaves, suffix, check_slave_present, NULL);
	if (err != 1) {
		snd_printdd("No slave found for %s\n", name);
		return 0;
	}
	kctl = snd_ctl_make_virtual_master(name, tlv);
	if (!kctl)
		return -ENOMEM;
	err = snd_hda_ctl_add(codec, 0, kctl);
	if (err < 0)
		return err;

	err = map_slaves(codec, slaves, suffix,
			 (map_slave_func_t)snd_ctl_add_slave, kctl);
	if (err < 0)
		return err;

	/* init with master mute & zero volume */
	put_kctl_with_value(kctl, 0);
	if (init_slave_vol)
		map_slaves(codec, slaves, suffix,
			   tlv ? init_slave_0dB : init_slave_unmute, kctl);

	if (ctl_ret)
		*ctl_ret = kctl;
	return 0;
}