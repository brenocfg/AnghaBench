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
struct snd_virmidi_dev {TYPE_1__* card; int /*<<< orphan*/  flags; } ;
struct snd_seq_port_subscribe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_VIRMIDI_SUBSCRIBE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_virmidi_unsubscribe(void *private_data,
				   struct snd_seq_port_subscribe *info)
{
	struct snd_virmidi_dev *rdev;

	rdev = private_data;
	rdev->flags &= ~SNDRV_VIRMIDI_SUBSCRIBE;
	module_put(rdev->card->module);
	return 0;
}