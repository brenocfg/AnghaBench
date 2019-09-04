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
typedef  int /*<<< orphan*/  dictType ;
struct TYPE_3__ {int rehashidx; scalar_t__ iterators; void* privdata; int /*<<< orphan*/ * type; int /*<<< orphan*/ * ht; } ;
typedef  TYPE_1__ dict ;

/* Variables and functions */
 int DICT_OK ; 
 int /*<<< orphan*/  _dictReset (int /*<<< orphan*/ *) ; 

int _dictInit(dict *d, dictType *type,
        void *privDataPtr)
{
    _dictReset(&d->ht[0]);
    _dictReset(&d->ht[1]);
    d->type = type;
    d->privdata = privDataPtr;
    d->rehashidx = -1;
    d->iterators = 0;
    return DICT_OK;
}