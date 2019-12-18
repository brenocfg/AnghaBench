#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  errstr; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_5__ {int /*<<< orphan*/  errstr; int /*<<< orphan*/  err; TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */

__attribute__((used)) static void __redisAsyncCopyError(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    ac->err = c->err;
    ac->errstr = c->errstr;
}