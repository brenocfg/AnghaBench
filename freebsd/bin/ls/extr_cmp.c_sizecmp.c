#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fts_name; TYPE_1__* fts_statp; } ;
struct TYPE_5__ {scalar_t__ st_size; } ;
typedef  TYPE_2__ FTSENT ;

/* Variables and functions */
 int strcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sizecmp(const FTSENT *a, const FTSENT *b)
{

	if (b->fts_statp->st_size > a->fts_statp->st_size)
		return (1);
	if (b->fts_statp->st_size < a->fts_statp->st_size)
		return (-1);
	return (strcoll(a->fts_name, b->fts_name));
}