#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Secure; int /*<<< orphan*/  Target; int /*<<< orphan*/  HeaderHostName; } ;
typedef  TYPE_1__ URL_DATA ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CreateUrl(char *url, UINT url_size, URL_DATA *data)
{
	char *protocol;
	// Validate arguments
	if (url == NULL || data == NULL)
	{
		return;
	}

	if (data->Secure == false)
	{
		protocol = "http://";
	}
	else
	{
		protocol = "https://";
	}

	Format(url, url_size, "%s%s%s", protocol, data->HeaderHostName, data->Target);
}