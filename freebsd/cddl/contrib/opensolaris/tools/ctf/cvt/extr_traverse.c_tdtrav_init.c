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
struct TYPE_3__ {int vgen; void* private; int /*<<< orphan*/ * postops; int /*<<< orphan*/ * preops; int /*<<< orphan*/ * firstops; } ;
typedef  TYPE_1__ tdtrav_data_t ;
typedef  int /*<<< orphan*/  tdtrav_cb_f ;

/* Variables and functions */
 int /*<<< orphan*/ * tdnops ; 

void
tdtrav_init(tdtrav_data_t *tdtd, int *vgenp, tdtrav_cb_f *firstops,
    tdtrav_cb_f *preops, tdtrav_cb_f *postops, void *private)
{
	tdtd->vgen = ++(*vgenp);
	tdtd->firstops = firstops ? firstops : tdnops;
	tdtd->preops = preops ? preops : tdnops;
	tdtd->postops = postops ? postops : tdnops;
	tdtd->private = private;
}