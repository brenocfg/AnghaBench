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
struct TYPE_4__ {scalar_t__ nodes_confirmed; scalar_t__ nodes_delivered; int /*<<< orphan*/  body; scalar_t__ queue; } ;
typedef  TYPE_1__ job ;

/* Variables and functions */
 int /*<<< orphan*/  decrRefCount (scalar_t__) ; 
 int /*<<< orphan*/  dictRelease (scalar_t__) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void freeJob(job *j) {
    if (j == NULL) return;
    if (j->queue) decrRefCount(j->queue);
    sdsfree(j->body);
    if (j->nodes_delivered) dictRelease(j->nodes_delivered);
    if (j->nodes_confirmed) dictRelease(j->nodes_confirmed);
    zfree(j);
}