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
struct lbs_private {int /*<<< orphan*/  enable11d; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11D_DOMAIN_INFO ; 
 int /*<<< orphan*/  CMD_ACT_SET ; 
 int /*<<< orphan*/  CMD_OPTION_WAITFORRSP ; 
 int /*<<< orphan*/  lbs_deb_11d (char*) ; 
 int lbs_prepare_and_send_command (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_domain_info_11d(struct lbs_private *priv)
{
	int ret;

	if (!priv->enable11d) {
		lbs_deb_11d("dnld domain Info with 11d disabled\n");
		return 0;
	}

	ret = lbs_prepare_and_send_command(priv, CMD_802_11D_DOMAIN_INFO,
				    CMD_ACT_SET,
				    CMD_OPTION_WAITFORRSP, 0, NULL);
	if (ret)
		lbs_deb_11d("fail to dnld domain info\n");

	return ret;
}