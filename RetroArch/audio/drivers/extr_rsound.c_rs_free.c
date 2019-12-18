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
struct TYPE_3__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  rd; } ;
typedef  TYPE_1__ rsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  rsd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_free(void *data)
{
   rsd_t *rsd = (rsd_t*)data;

   rsd_stop(rsd->rd);
   rsd_free(rsd->rd);

   fifo_free(rsd->buffer);
   slock_free(rsd->cond_lock);
   scond_free(rsd->cond);

   free(rsd);
}