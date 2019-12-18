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
struct p9_wstat {int dummy; } ;
struct p9_fcall {int size; int capacity; char* sdata; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  p9pdu_dump (int,struct p9_fcall*) ; 
 int p9pdu_readf (struct p9_fcall*,int,char*,struct p9_wstat*) ; 

int p9stat_read(char *buf, int len, struct p9_wstat *st, int dotu)
{
	struct p9_fcall fake_pdu;
	int ret;

	fake_pdu.size = len;
	fake_pdu.capacity = len;
	fake_pdu.sdata = buf;
	fake_pdu.offset = 0;

	ret = p9pdu_readf(&fake_pdu, dotu, "S", st);
	if (ret) {
		P9_DPRINTK(P9_DEBUG_9P, "<<< p9stat_read failed: %d\n", ret);
		p9pdu_dump(1, &fake_pdu);
	}

	return ret;
}