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
typedef  int /*<<< orphan*/  template ;
struct brcms_c_info {int /*<<< orphan*/  hw; TYPE_1__* pub; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_etheraddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ T_BA_TPL_BASE ; 
 int T_RAM_ACCESS_SZ ; 
 int /*<<< orphan*/  brcms_b_write_template_ram (int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void brcms_c_ampdu_macaddr_upd(struct brcms_c_info *wlc)
{
	char template[T_RAM_ACCESS_SZ * 2];

	/* driver needs to write the ta in the template; ta is at offset 16 */
	memset(template, 0, sizeof(template));
	memcpy(template, wlc->pub->cur_etheraddr, ETH_ALEN);
	brcms_b_write_template_ram(wlc->hw, (T_BA_TPL_BASE + 16),
				  (T_RAM_ACCESS_SZ * 2),
				  template);
}