#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  backends_mutex; TYPE_7__* backends; int /*<<< orphan*/  event_thread_count; } ;
typedef  TYPE_1__ network_backends_t ;
struct TYPE_10__ {scalar_t__ type; size_t weight; TYPE_6__* addr; } ;
typedef  TYPE_2__ network_backend_t ;
typedef  size_t guint ;
typedef  int gint ;
typedef  char gchar ;
typedef  scalar_t__ backend_type_t ;
struct TYPE_12__ {size_t len; TYPE_2__** pdata; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BACKEND_TYPE_RO ; 
 scalar_t__ BACKEND_TYPE_RW ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/  g_critical (char*,char*) ; 
 int /*<<< orphan*/  g_message (char*,char*,char*) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ptr_array_add (TYPE_7__*,TYPE_2__*) ; 
 scalar_t__ network_address_set_address (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  network_backend_free (TYPE_2__*) ; 
 TYPE_2__* network_backend_new (int /*<<< orphan*/ ) ; 
 scalar_t__ strleq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

int network_backends_add(network_backends_t *bs, /* const */ gchar *address, backend_type_t type) {
	network_backend_t *new_backend;
	guint i;

	new_backend = network_backend_new(bs->event_thread_count);
	new_backend->type = type;

	gchar *p = NULL;
	if (type == BACKEND_TYPE_RO) {
		guint weight = 1;
		p = strrchr(address, '@');
		if (p != NULL) {
			*p = '\0';
			weight = atoi(p+1);
		}
		new_backend->weight = weight;
	}

	if (0 != network_address_set_address(new_backend->addr, address)) {
		network_backend_free(new_backend);
		return -1;
	}

	/* check if this backend is already known */
	g_mutex_lock(bs->backends_mutex);	/*remove lock*/
	gint first_slave = -1;
	for (i = 0; i < bs->backends->len; i++) {
		network_backend_t *old_backend = bs->backends->pdata[i];

		if (first_slave == -1 && old_backend->type == BACKEND_TYPE_RO) first_slave = i;

		if (old_backend->type == type && strleq(S(old_backend->addr->name), S(new_backend->addr->name))) {
			network_backend_free(new_backend);

			g_mutex_unlock(bs->backends_mutex);	/*remove lock*/
			g_critical("backend %s is already known!", address);
			return -1;
		}
	}

	g_ptr_array_add(bs->backends, new_backend);
	if (first_slave != -1 && type == BACKEND_TYPE_RW) {
		network_backend_t *temp_backend = bs->backends->pdata[first_slave];
		bs->backends->pdata[first_slave] = bs->backends->pdata[bs->backends->len - 1];
		bs->backends->pdata[bs->backends->len - 1] = temp_backend;
	}
	g_mutex_unlock(bs->backends_mutex);	/*remove lock*/

	g_message("added %s backend: %s", (type == BACKEND_TYPE_RW) ? "read/write" : "read-only", address);

	if (p != NULL) *p = '@';

	return 0;
}