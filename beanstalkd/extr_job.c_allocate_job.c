#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int body_size; int /*<<< orphan*/  created_at; } ;
struct TYPE_8__ {char* body; TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  job_list_reset (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nanoseconds () ; 
 int /*<<< orphan*/  twarnx (char*) ; 

Job *
allocate_job(int body_size)
{
    Job *j;

    j = malloc(sizeof(Job) + body_size);
    if (!j) {
        twarnx("OOM");
        return (Job *) 0;
    }

    memset(j, 0, sizeof(Job));
    j->r.created_at = nanoseconds();
    j->r.body_size = body_size;
    j->body = (char *)j + sizeof(Job);
    job_list_reset(j);
    return j;
}