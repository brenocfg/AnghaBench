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
typedef  int u32 ;
typedef  int u16 ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  flash; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ifup ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int strncmp (char*,char const*,int) ; 

__attribute__((used)) static int ql_validate_flash(struct ql_adapter *qdev, u32 size, const char *str)
{
	int status, i;
	u16 csum = 0;
	__le16 *flash = (__le16 *)&qdev->flash;

	status = strncmp((char *)&qdev->flash, str, 4);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev, "Invalid flash signature.\n");
		return	status;
	}

	for (i = 0; i < size; i++)
		csum += le16_to_cpu(*flash++);

	if (csum)
		netif_err(qdev, ifup, qdev->ndev,
			  "Invalid flash checksum, csum = 0x%.04x.\n", csum);

	return csum;
}