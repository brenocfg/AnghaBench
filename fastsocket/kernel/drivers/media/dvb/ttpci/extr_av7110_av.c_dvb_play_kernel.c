#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct av7110 {int /*<<< orphan*/ * ipack; TYPE_1__ avout; int /*<<< orphan*/ * kbuf; } ;
typedef  unsigned long ssize_t ;

/* Variables and functions */
 unsigned long ENOBUFS ; 
 unsigned long EWOULDBLOCK ; 
 int /*<<< orphan*/  FREE_COND ; 
 int IPACKS ; 
 int /*<<< orphan*/  av7110_ipack_instant_repack (int /*<<< orphan*/  const*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dvb_play_kernel(struct av7110 *av7110, const u8 *buf,
			unsigned long count, int nonblock, int type)
{
	unsigned long todo = count, n;
	dprintk(2, "av7110:%p, \n", av7110);

	if (!av7110->kbuf[type])
		return -ENOBUFS;

	if (nonblock && !FREE_COND)
		return -EWOULDBLOCK;

	while (todo > 0) {
		if (!FREE_COND) {
			if (nonblock)
				return count - todo;
			if (wait_event_interruptible(av7110->avout.queue,
						     FREE_COND))
				return count - todo;
		}
		n = todo;
		if (n > IPACKS * 2)
			n = IPACKS * 2;
		av7110_ipack_instant_repack(buf, n, &av7110->ipack[type]);
		todo -= n;
		buf += n;
	}
	return count - todo;
}