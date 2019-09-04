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
typedef  int* uuid_t ;
typedef  int /*<<< orphan*/  uuid_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

void
uuid_unparse_lower(const uuid_t uu, uuid_string_t out)
{
	snprintf(out,
		sizeof(uuid_string_t),
		"%02x%02x%02x%02x-"
		"%02x%02x-"
		"%02x%02x-"
		"%02x%02x-"
		"%02x%02x%02x%02x%02x%02x",
		uu[0], uu[1], uu[2], uu[3],
		uu[4], uu[5],
		uu[6], uu[7],
		uu[8], uu[9],
		uu[10], uu[11], uu[12], uu[13], uu[14], uu[15]);
}