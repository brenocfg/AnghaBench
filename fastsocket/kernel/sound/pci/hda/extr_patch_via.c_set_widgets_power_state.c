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
struct via_spec {int /*<<< orphan*/  (* set_widgets_power_state ) (struct hda_codec*) ;} ;
struct hda_codec {struct via_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static void set_widgets_power_state(struct hda_codec *codec)
{
#if 0 /* FIXME: the assumed connections don't match always with the
       * actual routes by the generic parser, so better to disable
       * the control for safety.
       */
	struct via_spec *spec = codec->spec;
	if (spec->set_widgets_power_state)
		spec->set_widgets_power_state(codec);
#endif
}