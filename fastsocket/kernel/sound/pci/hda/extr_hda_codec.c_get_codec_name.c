#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct hda_vendor_id {scalar_t__ id; char* name; } ;
struct hda_codec {int vendor_id; void* chip_name; TYPE_1__* preset; void* vendor_name; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hda_vendor_id* hda_vendor_ids ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int get_codec_name(struct hda_codec *codec)
{
	const struct hda_vendor_id *c;
	const char *vendor = NULL;
	u16 vendor_id = codec->vendor_id >> 16;
	char tmp[16];

	if (codec->vendor_name)
		goto get_chip_name;

	for (c = hda_vendor_ids; c->id; c++) {
		if (c->id == vendor_id) {
			vendor = c->name;
			break;
		}
	}
	if (!vendor) {
		sprintf(tmp, "Generic %04x", vendor_id);
		vendor = tmp;
	}
	codec->vendor_name = kstrdup(vendor, GFP_KERNEL);
	if (!codec->vendor_name)
		return -ENOMEM;

 get_chip_name:
	if (codec->chip_name)
		return 0;

	if (codec->preset && codec->preset->name)
		codec->chip_name = kstrdup(codec->preset->name, GFP_KERNEL);
	else {
		sprintf(tmp, "ID %x", codec->vendor_id & 0xffff);
		codec->chip_name = kstrdup(tmp, GFP_KERNEL);
	}
	if (!codec->chip_name)
		return -ENOMEM;
	return 0;
}