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
struct aoa_codec {int /*<<< orphan*/ * gpio; int /*<<< orphan*/ * soundbus_dev; } ;

/* Variables and functions */
 int MAX_CODECS_PER_BUS ; 

__attribute__((used)) static void layout_remove_codec(struct aoa_codec *codec)
{
	int i;
	/* here remove the codec from the layout dev's
	 * codec reference */

	codec->soundbus_dev = NULL;
	codec->gpio = NULL;
	for (i=0; i<MAX_CODECS_PER_BUS; i++) {
	}
}