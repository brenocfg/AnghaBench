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
typedef  int uint16_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int resolution; } ;

/* Variables and functions */
 TYPE_1__* thisboard ; 

__attribute__((used)) static inline uint16_t munge_bipolar_sample(const struct comedi_device *dev,
					    uint16_t sample)
{
	sample += 1 << (thisboard->resolution - 1);
	return sample;
}