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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  IPToStr6 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetIP6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void IPToStr6Array(char *str, UINT size, UCHAR *bytes)
{
	IP ip;
	// Validate arguments
	if (str == NULL || bytes == NULL)
	{
		return;
	}

	SetIP6(&ip, bytes);

	IPToStr6(str, size, &ip);
}