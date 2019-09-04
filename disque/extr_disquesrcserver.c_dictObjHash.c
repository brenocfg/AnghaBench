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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 unsigned int dictGenHashFunction (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

unsigned int dictObjHash(const void *key) {
    const robj *o = key;
    return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
}