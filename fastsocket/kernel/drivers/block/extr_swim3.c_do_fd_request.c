#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_3__ {scalar_t__ media_bay; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_FD ; 
 scalar_t__ check_media_bay (scalar_t__,int /*<<< orphan*/ ) ; 
 int floppy_count ; 
 TYPE_1__* floppy_states ; 
 int /*<<< orphan*/  start_request (TYPE_1__*) ; 

__attribute__((used)) static void do_fd_request(struct request_queue * q)
{
	int i;
	for(i=0;i<floppy_count;i++)
	{
#ifdef CONFIG_PMAC_MEDIABAY
		if (floppy_states[i].media_bay &&
			check_media_bay(floppy_states[i].media_bay, MB_FD))
			continue;
#endif /* CONFIG_PMAC_MEDIABAY */
		start_request(&floppy_states[i]);
	}
}