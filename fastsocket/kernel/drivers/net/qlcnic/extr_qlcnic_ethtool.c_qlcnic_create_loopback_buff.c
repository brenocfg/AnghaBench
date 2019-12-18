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
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  random_data ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  QLCNIC_ILB_PKT_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_create_loopback_buff(unsigned char *data, u8 mac[])
{
	unsigned char random_data[] = {0xa8, 0x06, 0x45, 0x00};

	memset(data, 0x4e, QLCNIC_ILB_PKT_SIZE);

	memcpy(data, mac, ETH_ALEN);
	memcpy(data + ETH_ALEN, mac, ETH_ALEN);

	memcpy(data + 2 * ETH_ALEN, random_data, sizeof(random_data));
}