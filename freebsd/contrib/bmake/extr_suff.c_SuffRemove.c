#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ refCount; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  SuffFree (TYPE_1__*) ; 
 int /*<<< orphan*/  SuffUnRef (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sufflist ; 

__attribute__((used)) static void
SuffRemove(Lst l, Suff *s)
{
    SuffUnRef(l, s);
    if (s->refCount == 0) {
	SuffUnRef(sufflist, s);
	SuffFree(s);
    }
}