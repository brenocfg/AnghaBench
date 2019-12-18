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
struct strip {int sx_count; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/ * sx_buff; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DumpData (char*,struct strip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RecvErr(char *msg, struct strip *strip_info)
{
	__u8 *ptr = strip_info->sx_buff;
	__u8 *end = strip_info->sx_buff + strip_info->sx_count;
	DumpData(msg, strip_info, ptr, end);
	strip_info->rx_errors++;
}