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
struct hda_codec {int /*<<< orphan*/  chip_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alc_free (struct hda_codec*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alc_codec_rename(struct hda_codec *codec, const char *name)
{
	kfree(codec->chip_name);
	codec->chip_name = kstrdup(name, GFP_KERNEL);
	if (!codec->chip_name) {
		alc_free(codec);
		return -ENOMEM;
	}
	return 0;
}