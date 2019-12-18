#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_6__ {int* c; } ;
struct TYPE_5__ {int /*<<< orphan*/ * c; } ;
typedef  TYPE_1__ MetricomAddressString ;
typedef  TYPE_2__ MetricomAddress ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

__attribute__((used)) static __u8 *radio_address_to_string(const MetricomAddress * addr,
				     MetricomAddressString * p)
{
	sprintf(p->c, "%02X%02X-%02X%02X", addr->c[2], addr->c[3],
		addr->c[4], addr->c[5]);
	return (p->c);
}