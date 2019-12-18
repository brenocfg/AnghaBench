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
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int RTAS_UNKNOWN_SERVICE ; 
 int* of_get_property (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ rtas ; 

int rtas_token(const char *service)
{
	const int *tokp;
	if (rtas.dev == NULL)
		return RTAS_UNKNOWN_SERVICE;
	tokp = of_get_property(rtas.dev, service, NULL);
	return tokp ? *tokp : RTAS_UNKNOWN_SERVICE;
}