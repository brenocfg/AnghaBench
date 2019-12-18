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
struct gunzip_state {int dummy; } ;
typedef  int /*<<< orphan*/  discard_buf ;

/* Variables and functions */
 int /*<<< orphan*/  gunzip_exactly (struct gunzip_state*,char*,int) ; 

void gunzip_discard(struct gunzip_state *state, int len)
{
	static char discard_buf[128];

	while (len > sizeof(discard_buf)) {
		gunzip_exactly(state, discard_buf, sizeof(discard_buf));
		len -= sizeof(discard_buf);
	}

	if (len > 0)
		gunzip_exactly(state, discard_buf, len);
}