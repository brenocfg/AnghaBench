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
struct TYPE_2__ {int fd; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 scalar_t__ BUFSIZ ; 
 void* ckmalloc (scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* parsefile ; 
 scalar_t__ parselleft ; 
 scalar_t__ parsenleft ; 
 int plinno ; 
 int /*<<< orphan*/  pushfile () ; 

void
setinputfd(int fd, int push)
{
	if (push) {
		pushfile();
		parsefile->buf = ckmalloc(BUFSIZ + 1);
	}
	if (parsefile->fd > 0)
		close(parsefile->fd);
	parsefile->fd = fd;
	if (parsefile->buf == NULL)
		parsefile->buf = ckmalloc(BUFSIZ + 1);
	parselleft = parsenleft = 0;
	plinno = 1;
}