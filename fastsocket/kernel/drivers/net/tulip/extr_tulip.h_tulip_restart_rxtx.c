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
struct tulip_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tulip_start_rxtx (struct tulip_private*) ; 
 int /*<<< orphan*/  tulip_stop_rxtx (struct tulip_private*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void tulip_restart_rxtx(struct tulip_private *tp)
{
	tulip_stop_rxtx(tp);
	udelay(5);
	tulip_start_rxtx(tp);
}