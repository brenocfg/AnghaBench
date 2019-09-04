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
struct TYPE_5__ {int /*<<< orphan*/ * ht; } ;
typedef  TYPE_1__ dict ;

/* Variables and functions */
 int /*<<< orphan*/  _dictClear (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void dictRelease(dict *d)
{
    _dictClear(d,&d->ht[0],NULL);
    _dictClear(d,&d->ht[1],NULL);
    zfree(d);
}