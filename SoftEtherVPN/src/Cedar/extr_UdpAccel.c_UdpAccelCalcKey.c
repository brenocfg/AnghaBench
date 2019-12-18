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
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int UDP_ACCELERATION_COMMON_KEY_SIZE ; 
 int UDP_ACCELERATION_PACKET_IV_SIZE ; 

void UdpAccelCalcKey(UCHAR *key, UCHAR *common_key, UCHAR *iv)
{
	UCHAR tmp[UDP_ACCELERATION_COMMON_KEY_SIZE + UDP_ACCELERATION_PACKET_IV_SIZE];
	// Validate arguments
	if (key == NULL || common_key == NULL || iv == NULL)
	{
		return;
	}

	Copy(tmp, common_key, UDP_ACCELERATION_COMMON_KEY_SIZE);
	Copy(tmp + UDP_ACCELERATION_COMMON_KEY_SIZE, iv, UDP_ACCELERATION_PACKET_IV_SIZE);

	Sha1(key, tmp, sizeof(tmp));
}