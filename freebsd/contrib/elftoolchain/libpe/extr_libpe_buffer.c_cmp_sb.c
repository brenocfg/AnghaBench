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
struct TYPE_5__ {scalar_t__ pb_off; } ;
struct TYPE_6__ {TYPE_1__ sb_pb; } ;
typedef  TYPE_2__ PE_SecBuf ;

/* Variables and functions */

__attribute__((used)) static int
cmp_sb(PE_SecBuf *a, PE_SecBuf *b)
{

	if (a->sb_pb.pb_off < b->sb_pb.pb_off)
		return (-1);
	else if (a->sb_pb.pb_off == b->sb_pb.pb_off)
		return (0);
	else
		return (1);
}