#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ wpos; scalar_t__ wbase; scalar_t__ rpos; scalar_t__ rend; int /*<<< orphan*/  (* seek ) (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FFINALLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_file(FILE *f)
{
	if (!f) return;
	FFINALLOCK(f);
	if (f->wpos > f->wbase) f->write(f, 0, 0);
	if (f->rpos < f->rend) f->seek(f, f->rpos-f->rend, SEEK_CUR);
}