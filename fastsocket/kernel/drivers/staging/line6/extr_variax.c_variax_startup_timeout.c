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
struct TYPE_3__ {scalar_t__ ok; } ;
struct usb_line6_variax {TYPE_1__ dumpreq; int /*<<< orphan*/  line6; } ;

/* Variables and functions */
 int /*<<< orphan*/  line6_dump_request_async (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_startup_delayed (TYPE_1__*,int,void (*) (unsigned long),struct usb_line6_variax*) ; 

__attribute__((used)) static void variax_startup_timeout(unsigned long arg)
{
	struct usb_line6_variax *variax = (struct usb_line6_variax *)arg;

	if (variax->dumpreq.ok)
		return;

	line6_dump_request_async(&variax->dumpreq, &variax->line6, 0);
	line6_startup_delayed(&variax->dumpreq, 1, variax_startup_timeout,
			      variax);
}