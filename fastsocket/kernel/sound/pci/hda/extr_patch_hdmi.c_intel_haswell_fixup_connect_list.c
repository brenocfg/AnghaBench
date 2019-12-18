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
struct hdmi_spec {int num_cvts; int /*<<< orphan*/  cvt_nids; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int snd_hda_get_connections (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_conn_list (struct hda_codec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_haswell_fixup_connect_list(struct hda_codec *codec,
					     hda_nid_t nid)
{
	struct hdmi_spec *spec = codec->spec;
	hda_nid_t conns[4];
	int nconns;

	nconns = snd_hda_get_connections(codec, nid, conns, ARRAY_SIZE(conns));
	if (nconns == spec->num_cvts &&
	    !memcmp(conns, spec->cvt_nids, spec->num_cvts * sizeof(hda_nid_t)))
		return;

	/* override pins connection list */
	snd_printdd("hdmi: haswell: override pin connection 0x%x\n", nid);
	snd_hda_override_conn_list(codec, nid, spec->num_cvts, spec->cvt_nids);
}