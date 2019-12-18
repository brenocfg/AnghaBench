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
struct snd_opl4 {int dummy; } ;
struct snd_device {struct snd_opl4* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_opl4_free (struct snd_opl4*) ; 

__attribute__((used)) static int snd_opl4_dev_free(struct snd_device *device)
{
	struct snd_opl4 *opl4 = device->device_data;
	snd_opl4_free(opl4);
	return 0;
}