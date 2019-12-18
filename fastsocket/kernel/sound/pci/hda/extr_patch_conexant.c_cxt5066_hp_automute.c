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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  hp_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  HP_PRESENT_PORT_A ; 
 int /*<<< orphan*/  HP_PRESENT_PORT_D ; 
 int /*<<< orphan*/  cxt5066_update_speaker (struct hda_codec*) ; 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxt5066_hp_automute(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int portA, portD;

	/* Port A */
	portA = snd_hda_jack_detect(codec, 0x19);

	/* Port D */
	portD = snd_hda_jack_detect(codec, 0x1c);

	spec->hp_present = portA ? HP_PRESENT_PORT_A : 0;
	spec->hp_present |= portD ? HP_PRESENT_PORT_D : 0;
	snd_printdd("CXT5066: hp automute portA=%x portD=%x present=%d\n",
		portA, portD, spec->hp_present);
	cxt5066_update_speaker(codec);
}