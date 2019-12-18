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
struct nid_path {int /*<<< orphan*/ * path; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_WCAP_OUT_AMP ; 
 unsigned int AC_WID_PIN ; 
 unsigned int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int get_wcaps_type (unsigned int) ; 

__attribute__((used)) static bool has_amp_out(struct hda_codec *codec, struct nid_path *path, int idx)
{
	hda_nid_t nid = path->path[idx];
	unsigned int caps = get_wcaps(codec, nid);
	unsigned int type = get_wcaps_type(caps);

	if (!(caps & AC_WCAP_OUT_AMP))
		return false;
	if (type == AC_WID_PIN && !idx) /* only for output pins */
		return false;
	return true;
}