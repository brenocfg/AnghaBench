#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* raw_pwds; TYPE_3__* raw_ips; struct TYPE_5__* default_file; int /*<<< orphan*/  global_wrr; int /*<<< orphan*/  backends_mutex; TYPE_3__* backends; } ;
typedef  TYPE_1__ network_backends_t ;
typedef  int /*<<< orphan*/  network_backend_t ;
typedef  size_t gsize ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/ ** pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_mutex_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_wrr_poll_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_backend_free (int /*<<< orphan*/ *) ; 

void network_backends_free(network_backends_t *bs) {
	gsize i;

	if (!bs) return;

	g_mutex_lock(bs->backends_mutex);	/*remove lock*/
	for (i = 0; i < bs->backends->len; i++) {
		network_backend_t *backend = bs->backends->pdata[i];
		
		network_backend_free(backend);
	}
	g_mutex_unlock(bs->backends_mutex);	/*remove lock*/

	g_ptr_array_free(bs->backends, TRUE);
	g_mutex_free(bs->backends_mutex);	/*remove lock*/

	g_wrr_poll_free(bs->global_wrr);
	g_free(bs->default_file);

	g_ptr_array_free(bs->raw_ips, TRUE);
	g_ptr_array_free(bs->raw_pwds, TRUE);

	g_free(bs);
}