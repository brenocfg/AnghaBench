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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int RTAX_MAX ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int) ; 

void
mib_extract_addrs(int addrs, u_char *info, struct sockaddr **out)
{
	u_int i;

	for (i = 0; i < RTAX_MAX; i++) {
		if ((addrs & (1 << i)) != 0) {
			*out = (struct sockaddr *)(void *)info;
			info += roundup((*out)->sa_len, sizeof(long));
		} else
			*out = NULL;
		out++;
	}
}