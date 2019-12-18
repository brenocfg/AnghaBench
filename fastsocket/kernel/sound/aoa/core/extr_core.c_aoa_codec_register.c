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
struct aoa_codec {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int attach_codec_to_fabric (struct aoa_codec*) ; 
 int /*<<< orphan*/  codec_list ; 
 scalar_t__ fabric ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int aoa_codec_register(struct aoa_codec *codec)
{
	int err = 0;

	/* if there's a fabric already, we can tell if we
	 * will want to have this codec, so propagate error
	 * through. Otherwise, this will happen later... */
	if (fabric)
		err = attach_codec_to_fabric(codec);
	if (!err)
		list_add(&codec->list, &codec_list);
	return err;
}