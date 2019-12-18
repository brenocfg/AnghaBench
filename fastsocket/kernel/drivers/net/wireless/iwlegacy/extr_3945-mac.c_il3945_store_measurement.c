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
typedef  char u8 ;
struct TYPE_4__ {int /*<<< orphan*/  last_tsf; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct il_priv {TYPE_2__ _3945; TYPE_1__ active; } ;
struct ieee80211_measurement_params {char channel; int /*<<< orphan*/  duration; int /*<<< orphan*/  start_time; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,char,char,char const*) ; 
 char IL_MEASURE_BASIC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct il_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  il3945_get_measurement (struct il_priv*,struct ieee80211_measurement_params*,char) ; 
 char le16_to_cpu (int /*<<< orphan*/ ) ; 
 char simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static ssize_t
il3945_store_measurement(struct device *d, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct il_priv *il = dev_get_drvdata(d);
	struct ieee80211_measurement_params params = {
		.channel = le16_to_cpu(il->active.channel),
		.start_time = cpu_to_le64(il->_3945.last_tsf),
		.duration = cpu_to_le16(1),
	};
	u8 type = IL_MEASURE_BASIC;
	u8 buffer[32];
	u8 channel;

	if (count) {
		char *p = buffer;
		strlcpy(buffer, buf, sizeof(buffer));
		channel = simple_strtoul(p, NULL, 0);
		if (channel)
			params.channel = channel;

		p = buffer;
		while (*p && *p != ' ')
			p++;
		if (*p)
			type = simple_strtoul(p + 1, NULL, 0);
	}

	D_INFO("Invoking measurement of type %d on " "channel %d (for '%s')\n",
	       type, params.channel, buf);
	il3945_get_measurement(il, &params, type);

	return count;
}