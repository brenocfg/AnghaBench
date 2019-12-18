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
struct hda_codec {scalar_t__ vendor_id; } ;
struct alc_codec_rename_table {scalar_t__ vendor_id; int coef_mask; int coef_bits; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int alc_codec_rename (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int alc_get_coef0 (struct hda_codec*) ; 
 struct alc_codec_rename_table* rename_tbl ; 

__attribute__((used)) static int alc_codec_rename_from_preset(struct hda_codec *codec)
{
	const struct alc_codec_rename_table *p;

	for (p = rename_tbl; p->vendor_id; p++) {
		if (p->vendor_id != codec->vendor_id)
			continue;
		if ((alc_get_coef0(codec) & p->coef_mask) == p->coef_bits)
			return alc_codec_rename(codec, p->name);
	}
	return 0;
}