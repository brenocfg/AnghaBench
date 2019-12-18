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
struct string_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_ssids ) (struct string_list*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct string_list*) ; 
 TYPE_1__* wifi_driver ; 

void driver_wifi_get_ssids(struct string_list* ssids)
{
   wifi_driver->get_ssids(ssids);
}