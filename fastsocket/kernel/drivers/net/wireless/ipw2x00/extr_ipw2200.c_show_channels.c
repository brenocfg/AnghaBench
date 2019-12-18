#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct libipw_geo {int bg_channels; int a_channels; TYPE_2__* a; TYPE_1__* bg; } ;
struct ipw_priv {int /*<<< orphan*/  ieee; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int channel; int flags; } ;
struct TYPE_3__ {int channel; int flags; } ;

/* Variables and functions */
 int LIBIPW_CH_B_ONLY ; 
 int LIBIPW_CH_NO_IBSS ; 
 int LIBIPW_CH_PASSIVE_ONLY ; 
 int LIBIPW_CH_RADAR_DETECT ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 struct libipw_geo* libipw_get_geo (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t show_channels(struct device *d,
			     struct device_attribute *attr,
			     char *buf)
{
	struct ipw_priv *priv = dev_get_drvdata(d);
	const struct libipw_geo *geo = libipw_get_geo(priv->ieee);
	int len = 0, i;

	len = sprintf(&buf[len],
		      "Displaying %d channels in 2.4Ghz band "
		      "(802.11bg):\n", geo->bg_channels);

	for (i = 0; i < geo->bg_channels; i++) {
		len += sprintf(&buf[len], "%d: BSS%s%s, %s, Band %s.\n",
			       geo->bg[i].channel,
			       geo->bg[i].flags & LIBIPW_CH_RADAR_DETECT ?
			       " (radar spectrum)" : "",
			       ((geo->bg[i].flags & LIBIPW_CH_NO_IBSS) ||
				(geo->bg[i].flags & LIBIPW_CH_RADAR_DETECT))
			       ? "" : ", IBSS",
			       geo->bg[i].flags & LIBIPW_CH_PASSIVE_ONLY ?
			       "passive only" : "active/passive",
			       geo->bg[i].flags & LIBIPW_CH_B_ONLY ?
			       "B" : "B/G");
	}

	len += sprintf(&buf[len],
		       "Displaying %d channels in 5.2Ghz band "
		       "(802.11a):\n", geo->a_channels);
	for (i = 0; i < geo->a_channels; i++) {
		len += sprintf(&buf[len], "%d: BSS%s%s, %s.\n",
			       geo->a[i].channel,
			       geo->a[i].flags & LIBIPW_CH_RADAR_DETECT ?
			       " (radar spectrum)" : "",
			       ((geo->a[i].flags & LIBIPW_CH_NO_IBSS) ||
				(geo->a[i].flags & LIBIPW_CH_RADAR_DETECT))
			       ? "" : ", IBSS",
			       geo->a[i].flags & LIBIPW_CH_PASSIVE_ONLY ?
			       "passive only" : "active/passive");
	}

	return len;
}