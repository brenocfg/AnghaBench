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
typedef  int /*<<< orphan*/  u8 ;
struct ethtool_eeprom {unsigned int len; unsigned int offset; } ;
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  outbuf ;
typedef  int /*<<< orphan*/  inbuf ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EIO ; 
 unsigned int ETH_MODULE_SFF_8079_LEN ; 
 int /*<<< orphan*/  GET_PHY_MEDIA_INFO_IN_PAGE ; 
 int /*<<< orphan*/  GET_PHY_MEDIA_INFO_OUT_DATALEN ; 
 unsigned int MCDI_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  MC_CMD_GET_PHY_MEDIA_INFO ; 
 int MC_CMD_GET_PHY_MEDIA_INFO_IN_LEN ; 
 unsigned int MC_CMD_GET_PHY_MEDIA_INFO_OUT_DATA_OFST ; 
 int MC_CMD_GET_PHY_MEDIA_INFO_OUT_LENMAX ; 
 unsigned int SFP_NUM_PAGES ; 
 unsigned int SFP_PAGE_SIZE ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int efx_mcdi_phy_get_module_eeprom(struct efx_nic *efx,
					  struct ethtool_eeprom *ee, u8 *data)
{
	u8 outbuf[MC_CMD_GET_PHY_MEDIA_INFO_OUT_LENMAX];
	u8 inbuf[MC_CMD_GET_PHY_MEDIA_INFO_IN_LEN];
	size_t outlen;
	int rc;
	unsigned int payload_len;
	unsigned int space_remaining = ee->len;
	unsigned int page;
	unsigned int page_off;
	unsigned int to_copy;
	u8 *user_data = data;

	BUILD_BUG_ON(SFP_PAGE_SIZE * SFP_NUM_PAGES != ETH_MODULE_SFF_8079_LEN);

	page_off = ee->offset % SFP_PAGE_SIZE;
	page = ee->offset / SFP_PAGE_SIZE;

	while (space_remaining && (page < SFP_NUM_PAGES)) {
		MCDI_SET_DWORD(inbuf, GET_PHY_MEDIA_INFO_IN_PAGE, page);

		rc = efx_mcdi_rpc(efx, MC_CMD_GET_PHY_MEDIA_INFO,
				  inbuf, sizeof(inbuf),
				  outbuf, sizeof(outbuf),
				  &outlen);
		if (rc)
			return rc;

		if (outlen < (MC_CMD_GET_PHY_MEDIA_INFO_OUT_DATA_OFST +
			      SFP_PAGE_SIZE))
			return -EIO;

		payload_len = MCDI_DWORD(outbuf,
					 GET_PHY_MEDIA_INFO_OUT_DATALEN);
		if (payload_len != SFP_PAGE_SIZE)
			return -EIO;

		/* Copy as much as we can into data */
		payload_len -= page_off;
		to_copy = (space_remaining < payload_len) ?
			space_remaining : payload_len;

		memcpy(user_data,
		       outbuf + page_off +
		       MC_CMD_GET_PHY_MEDIA_INFO_OUT_DATA_OFST,
		       to_copy);

		space_remaining -= to_copy;
		user_data += to_copy;
		page_off = 0;
		page++;
	}

	return 0;
}