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
struct snd_jack {struct snd_jack* id; int /*<<< orphan*/  input_dev; scalar_t__ registered; int /*<<< orphan*/  (* private_free ) (struct snd_jack*) ;} ;
struct snd_device {struct snd_jack* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_jack*) ; 
 int /*<<< orphan*/  stub1 (struct snd_jack*) ; 

__attribute__((used)) static int snd_jack_dev_free(struct snd_device *device)
{
	struct snd_jack *jack = device->device_data;

	if (jack->private_free)
		jack->private_free(jack);

	/* If the input device is registered with the input subsystem
	 * then we need to use a different deallocator. */
	if (jack->registered)
		input_unregister_device(jack->input_dev);
	else
		input_free_device(jack->input_dev);

	kfree(jack->id);
	kfree(jack);

	return 0;
}