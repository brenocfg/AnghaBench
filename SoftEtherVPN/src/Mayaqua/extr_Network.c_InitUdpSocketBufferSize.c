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
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  SetSocketBufferSizeWithBestEffort (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDP_MAX_BUFFER_SIZE ; 

void InitUdpSocketBufferSize(SOCKET s)
{
	SetSocketBufferSizeWithBestEffort(s, true, UDP_MAX_BUFFER_SIZE);
	SetSocketBufferSizeWithBestEffort(s, false, UDP_MAX_BUFFER_SIZE);
}