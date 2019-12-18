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
struct TYPE_5__ {int /*<<< orphan*/  backends_mutex; TYPE_1__* backends; } ;
typedef  TYPE_2__ network_backends_t ;
typedef  int /*<<< orphan*/  guint ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 

guint network_backends_count(network_backends_t *bs) {
	guint len;

	g_mutex_lock(bs->backends_mutex);	/*remove lock*/
	len = bs->backends->len;
	g_mutex_unlock(bs->backends_mutex);	/*remove lock*/

	return len;
}