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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int /*<<< orphan*/  init_amp; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_INIT_DEFAULT ; 
 int /*<<< orphan*/  alc_subsystem_id (struct hda_codec*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 

__attribute__((used)) static void alc_ssid_check(struct hda_codec *codec, const hda_nid_t *ports)
{
	if (!alc_subsystem_id(codec, ports[0], ports[1], ports[2], ports[3])) {
		struct alc_spec *spec = codec->spec;
		snd_printd("realtek: "
			   "Enable default setup for auto mode as fallback\n");
		spec->init_amp = ALC_INIT_DEFAULT;
	}
}