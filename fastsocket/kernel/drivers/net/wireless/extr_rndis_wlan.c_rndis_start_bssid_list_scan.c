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
typedef  int /*<<< orphan*/  tmp ;
struct usbnet {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  OID_802_11_BSSID_LIST_SCAN ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int rndis_set_oid (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rndis_start_bssid_list_scan(struct usbnet *usbdev)
{
	__le32 tmp;

	/* Note: OID_802_11_BSSID_LIST_SCAN clears internal BSS list. */
	tmp = cpu_to_le32(1);
	return rndis_set_oid(usbdev, OID_802_11_BSSID_LIST_SCAN, &tmp,
							sizeof(tmp));
}