#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wastrue; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ CondIncl ;

/* Variables and functions */
 int /*<<< orphan*/  IN_THEN ; 
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static CondIncl *make_cond_incl(bool wastrue) {
    CondIncl *r = calloc(1, sizeof(CondIncl));
    r->ctx = IN_THEN;
    r->wastrue = wastrue;
    return r;
}