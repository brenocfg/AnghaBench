#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* server; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ gpsd_info ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GPSD_PORT ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void gpsd_init(gpsd_info *gpsd)
{
   memset(gpsd, 0, sizeof(gpsd_info));
   gpsd->server = "localhost";
   gpsd->port = DEFAULT_GPSD_PORT;
}