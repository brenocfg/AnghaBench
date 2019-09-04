#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ etime; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;
struct TYPE_5__ {scalar_t__ unixtime; } ;

/* Variables and functions */
 int getRawTTLFromJobID (int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 

void setJobTTLFromID(job *job) {
    int expire_minutes = getRawTTLFromJobID(job->id);
    /* Convert back to absolute unix time. */
    job->etime = server.unixtime + expire_minutes*60;
}