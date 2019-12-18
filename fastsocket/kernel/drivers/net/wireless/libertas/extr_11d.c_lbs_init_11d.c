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
struct parsed_region_chan_11d {int dummy; } ;
struct lbs_private {int /*<<< orphan*/  parsed_region_chan; scalar_t__ enable11d; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void lbs_init_11d(struct lbs_private *priv)
{
	priv->enable11d = 0;
	memset(&(priv->parsed_region_chan), 0,
	       sizeof(struct parsed_region_chan_11d));
	return;
}