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
struct TYPE_6__ {TYPE_1__* tail; } ;
typedef  TYPE_2__ Wal ;
struct TYPE_5__ {int free; } ;

/* Variables and functions */
 scalar_t__ makenextfile (TYPE_2__*) ; 

__attribute__((used)) static int
needfree(Wal *w, int n)
{
    if (w->tail->free >= n) return n;
    if (makenextfile(w)) return n;
    return 0;
}