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
struct natt_status {int dummy; } ;

/* Variables and functions */

bool natt_read(struct natt_status *status)
{
   /* MiniUPNPC is always synchronous, so there's nothing to read here.
    * Reserved for future backends. */
   return false;
}