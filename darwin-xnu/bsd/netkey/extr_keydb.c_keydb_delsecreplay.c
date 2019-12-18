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
struct secreplay {struct secreplay* bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SECA ; 
 int /*<<< orphan*/  _FREE (struct secreplay*,int /*<<< orphan*/ ) ; 

void
keydb_delsecreplay(struct secreplay *p)
{
	if (p->bitmap)
		_FREE(p->bitmap, M_SECA);
	_FREE(p, M_SECA);
}