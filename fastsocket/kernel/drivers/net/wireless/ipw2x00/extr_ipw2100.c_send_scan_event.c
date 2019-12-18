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
struct TYPE_2__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct ipw2100_priv {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_scan_event(void *data)
{
	struct ipw2100_priv *priv = data;
	union iwreq_data wrqu;

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(priv->net_dev, SIOCGIWSCAN, &wrqu, NULL);
}