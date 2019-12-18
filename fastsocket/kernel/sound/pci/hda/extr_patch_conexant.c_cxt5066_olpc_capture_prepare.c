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
struct conexant_spec {int recording; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxt5066_olpc_select_mic (struct hda_codec*) ; 

__attribute__((used)) static void cxt5066_olpc_capture_prepare(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	/* mark as recording and configure the microphone widget so that the
	 * recording LED comes on. */
	spec->recording = 1;
	cxt5066_olpc_select_mic(codec);
}