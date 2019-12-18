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
struct pppoatm_vcc {int dummy; } ;
struct ppp_channel {scalar_t__ private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct pppoatm_vcc *chan_to_pvcc(const struct ppp_channel *chan)
{
	return (struct pppoatm_vcc *) (chan->private);
}