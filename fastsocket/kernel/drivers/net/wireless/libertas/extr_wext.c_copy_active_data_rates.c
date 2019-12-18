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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  rates; } ;
struct lbs_private {scalar_t__ connect_status; scalar_t__ mesh_connect_status; TYPE_1__ curbssparams; } ;

/* Variables and functions */
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  MAX_RATES ; 
 int /*<<< orphan*/  lbs_bg_rates ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_active_data_rates(struct lbs_private *priv, u8 *rates)
{
	lbs_deb_enter(LBS_DEB_WEXT);

	if ((priv->connect_status != LBS_CONNECTED) &&
		(priv->mesh_connect_status != LBS_CONNECTED))
		memcpy(rates, lbs_bg_rates, MAX_RATES);
	else
		memcpy(rates, priv->curbssparams.rates, MAX_RATES);

	lbs_deb_leave(LBS_DEB_WEXT);
}