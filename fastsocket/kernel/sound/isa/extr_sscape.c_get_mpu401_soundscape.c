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
struct soundscape {int dummy; } ;
struct snd_mpu401 {scalar_t__ private_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct soundscape *get_mpu401_soundscape(struct snd_mpu401 * mpu)
{
	return (struct soundscape *) (mpu->private_data);
}