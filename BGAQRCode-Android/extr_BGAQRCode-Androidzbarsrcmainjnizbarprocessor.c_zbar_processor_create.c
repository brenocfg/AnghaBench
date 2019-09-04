#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int threaded; int /*<<< orphan*/  mutex; int /*<<< orphan*/  scanner; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_MOD_PROCESSOR ; 
 int /*<<< orphan*/  _zbar_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_processor_init (TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  err_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_image_scanner_create () ; 

zbar_processor_t *zbar_processor_create (int threaded)
{
    zbar_processor_t *proc = calloc(1, sizeof(zbar_processor_t));
    if(!proc)
        return(NULL);
    err_init(&proc->err, ZBAR_MOD_PROCESSOR);

    proc->scanner = zbar_image_scanner_create();
    if(!proc->scanner) {
        free(proc);
        return(NULL);
    }

    proc->threaded = !_zbar_mutex_init(&proc->mutex) && threaded;
    _zbar_processor_init(proc);
    return(proc);
}