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
typedef  int u64 ;
struct wl1251 {int dummy; } ;
struct acx_tsf_info {int current_tsf_lsb; scalar_t__ current_tsf_msb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_TSF_INFO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_tsf_info*) ; 
 struct acx_tsf_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_interrogate (struct wl1251*,int /*<<< orphan*/ ,struct acx_tsf_info*,int) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 

int wl1251_acx_tsf_info(struct wl1251 *wl, u64 *mactime)
{
	struct acx_tsf_info *tsf_info;
	int ret;

	tsf_info = kzalloc(sizeof(*tsf_info), GFP_KERNEL);
	if (!tsf_info) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wl1251_cmd_interrogate(wl, ACX_TSF_INFO,
				     tsf_info, sizeof(*tsf_info));
	if (ret < 0) {
		wl1251_warning("ACX_FW_REV interrogate failed");
		goto out;
	}

	*mactime = tsf_info->current_tsf_lsb |
		((u64)tsf_info->current_tsf_msb << 32);

out:
	kfree(tsf_info);
	return ret;
}