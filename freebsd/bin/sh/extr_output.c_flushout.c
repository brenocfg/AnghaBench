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
struct output {scalar_t__ fd; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * nextc; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_ERR ; 
 scalar_t__ xwrite (scalar_t__,int /*<<< orphan*/ *,int) ; 

void
flushout(struct output *dest)
{

	if (dest->buf == NULL || dest->nextc == dest->buf || dest->fd < 0)
		return;
	if (xwrite(dest->fd, dest->buf, dest->nextc - dest->buf) < 0)
		dest->flags |= OUTPUT_ERR;
	dest->nextc = dest->buf;
}