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
typedef  int /*<<< orphan*/  unchar ;
struct tipc_media_addr {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *eth_addr2str(struct tipc_media_addr *a, char *str_buf, int str_size)
{
	unchar *addr = (unchar *)&a->dev_addr;

	if (str_size < 18)
		*str_buf = '\0';
	else
		sprintf(str_buf, "%pM", addr);
	return str_buf;
}