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
typedef  int u8 ;
struct device {int feature_len; } ;

/* Variables and functions */
 unsigned int CHAR_BIT ; 
 int* get_feature_bits (struct device*) ; 

__attribute__((used)) static bool accepted_feature(struct device *dev, unsigned int bit)
{
	const u8 *features = get_feature_bits(dev) + dev->feature_len;

	if (dev->feature_len < bit / CHAR_BIT)
		return false;
	return features[bit / CHAR_BIT] & (1 << (bit % CHAR_BIT));
}