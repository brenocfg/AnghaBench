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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/ * rf; TYPE_1__* ops; } ;
struct TYPE_2__ {int rf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline void rt2x00_rf_read(struct rt2x00_dev *rt2x00dev,
				  const unsigned int word, u32 *data)
{
	BUG_ON(word < 1 || word > rt2x00dev->ops->rf_size / sizeof(u32));
	*data = rt2x00dev->rf[word - 1];
}