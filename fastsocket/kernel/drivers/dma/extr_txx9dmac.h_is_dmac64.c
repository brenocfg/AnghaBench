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
struct txx9dmac_chan {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int __is_dmac64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_dmac64(const struct txx9dmac_chan *dc)
{
	return __is_dmac64(dc->ddev);
}