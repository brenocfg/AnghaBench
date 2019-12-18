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
typedef  int u8 ;
struct device {unsigned int feature_len; TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int feature_len; scalar_t__ config_len; } ;

/* Variables and functions */
 unsigned int CHAR_BIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int* get_feature_bits (struct device*) ; 

__attribute__((used)) static void add_feature(struct device *dev, unsigned bit)
{
	u8 *features = get_feature_bits(dev);

	/* We can't extend the feature bits once we've added config bytes */
	if (dev->desc->feature_len <= bit / CHAR_BIT) {
		assert(dev->desc->config_len == 0);
		dev->feature_len = dev->desc->feature_len = (bit/CHAR_BIT) + 1;
	}

	features[bit / CHAR_BIT] |= (1 << (bit % CHAR_BIT));
}