#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tallies32; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  prism2_info_commtallies16 (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  prism2_info_commtallies32 (TYPE_1__*,unsigned char*,int) ; 

__attribute__((used)) static void prism2_info_commtallies(local_info_t *local, unsigned char *buf,
				    int left)
{
	if (local->tallies32)
		prism2_info_commtallies32(local, buf, left);
	else
		prism2_info_commtallies16(local, buf, left);
}