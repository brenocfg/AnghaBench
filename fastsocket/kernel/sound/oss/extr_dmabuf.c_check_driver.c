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
struct audio_driver {int /*<<< orphan*/ * set_channels; int /*<<< orphan*/ * set_bits; int /*<<< orphan*/ * set_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/ * default_set_bits ; 
 int /*<<< orphan*/ * default_set_channels ; 
 int /*<<< orphan*/ * default_set_speed ; 

__attribute__((used)) static void check_driver(struct audio_driver *d)
{
	if (d->set_speed == NULL)
		d->set_speed = default_set_speed;
	if (d->set_bits == NULL)
		d->set_bits = default_set_bits;
	if (d->set_channels == NULL)
		d->set_channels = default_set_channels;
}