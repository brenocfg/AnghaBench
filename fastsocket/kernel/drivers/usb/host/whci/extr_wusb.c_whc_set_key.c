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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct whc {scalar_t__ base; TYPE_1__* umc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WUSBSECKEY ; 
 scalar_t__ WUSBSETSECKEYCMD ; 
 int WUSBSETSECKEYCMD_GTK ; 
 int WUSBSETSECKEYCMD_IDX (int /*<<< orphan*/ ) ; 
 int WUSBSETSECKEYCMD_SET ; 
 scalar_t__ WUSBTKID ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,size_t) ; 
 int whci_wait_for (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int whc_set_key(struct whc *whc, u8 key_index, uint32_t tkid,
		       const void *key, size_t key_size, bool is_gtk)
{
	uint32_t setkeycmd;
	uint32_t seckey[4];
	int i;
	int ret;

	memcpy(seckey, key, key_size);
	setkeycmd = WUSBSETSECKEYCMD_SET | WUSBSETSECKEYCMD_IDX(key_index);
	if (is_gtk)
		setkeycmd |= WUSBSETSECKEYCMD_GTK;

	le_writel(tkid, whc->base + WUSBTKID);
	for (i = 0; i < 4; i++)
		le_writel(seckey[i], whc->base + WUSBSECKEY + 4*i);
	le_writel(setkeycmd, whc->base + WUSBSETSECKEYCMD);

	ret = whci_wait_for(&whc->umc->dev, whc->base + WUSBSETSECKEYCMD,
			    WUSBSETSECKEYCMD_SET, 0, 100, "set key");

	return ret;
}