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
struct TYPE_2__ {scalar_t__ descs; } ;
struct ns83820 {TYPE_1__ rx_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDSTS_OWN ; 
 unsigned int DESC_SIZE ; 
 int /*<<< orphan*/  build_rx_desc (struct ns83820*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_rx_desc(struct ns83820 *dev, unsigned i)
{
	build_rx_desc(dev, dev->rx_info.descs + (DESC_SIZE * i), 0, 0, CMDSTS_OWN, 0);
}