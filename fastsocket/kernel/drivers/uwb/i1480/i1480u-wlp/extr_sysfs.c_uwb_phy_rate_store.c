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
struct wlp_options {int /*<<< orphan*/  def_tx_hdr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int UWB_PHY_RATE_INVALID ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 int /*<<< orphan*/  wlp_tx_hdr_set_phy_rate (int /*<<< orphan*/ *,unsigned int) ; 

ssize_t uwb_phy_rate_store(struct wlp_options *options,
			   const char *buf, size_t size)
{
	ssize_t result;
	unsigned rate;

	result = sscanf(buf, "%u\n", &rate);
	if (result != 1) {
		result = -EINVAL;
		goto out;
	}
	result = -EINVAL;
	if (rate >= UWB_PHY_RATE_INVALID)
		goto out;
	wlp_tx_hdr_set_phy_rate(&options->def_tx_hdr, rate);
	result = 0;
out:
	return result < 0 ? result : size;
}