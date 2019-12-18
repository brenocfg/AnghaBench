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
struct s2255_fh {int resources; struct s2255_channel* channel; } ;
struct s2255_channel {int resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int res_get(struct s2255_fh *fh)
{
	struct s2255_channel *channel = fh->channel;
	/* is it free? */
	if (channel->resources)
		return 0; /* no, someone else uses it */
	/* it's free, grab it */
	channel->resources = 1;
	fh->resources = 1;
	dprintk(1, "s2255: res: get\n");
	return 1;
}