#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  td_mergelock; struct TYPE_5__* td_parname; struct TYPE_5__* td_parlabel; int /*<<< orphan*/  td_fwdlist; int /*<<< orphan*/  td_idhash; int /*<<< orphan*/  td_layouthash; int /*<<< orphan*/  td_iihash; } ;
typedef  TYPE_1__ tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iidesc_free ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdata_label_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * tdesc_free_cb ; 

void
tdata_free(tdata_t *td)
{
	hash_free(td->td_iihash, iidesc_free, NULL);
	hash_free(td->td_layouthash, tdesc_free_cb, NULL);
	hash_free(td->td_idhash, NULL, NULL);
	list_free(td->td_fwdlist, NULL, NULL);

	tdata_label_free(td);

	free(td->td_parlabel);
	free(td->td_parname);

	pthread_mutex_destroy(&td->td_mergelock);

	free(td);
}