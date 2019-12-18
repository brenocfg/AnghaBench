#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct fscache_object {TYPE_2__* cookie; } ;
typedef  enum fscache_checkaux { ____Placeholder_fscache_checkaux } fscache_checkaux ;
struct TYPE_4__ {int /*<<< orphan*/  netfs_data; TYPE_1__* def; } ;
struct TYPE_3__ {int (* check_aux ) (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FSCACHE_CHECKAUX_NEEDS_UPDATE 130 
#define  FSCACHE_CHECKAUX_OBSOLETE 129 
#define  FSCACHE_CHECKAUX_OKAY 128 
 int /*<<< orphan*/  fscache_n_checkaux_none ; 
 int /*<<< orphan*/  fscache_n_checkaux_obsolete ; 
 int /*<<< orphan*/  fscache_n_checkaux_okay ; 
 int /*<<< orphan*/  fscache_n_checkaux_update ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

enum fscache_checkaux fscache_check_aux(struct fscache_object *object,
					const void *data, uint16_t datalen)
{
	enum fscache_checkaux result;

	if (!object->cookie->def->check_aux) {
		fscache_stat(&fscache_n_checkaux_none);
		return FSCACHE_CHECKAUX_OKAY;
	}

	result = object->cookie->def->check_aux(object->cookie->netfs_data,
						data, datalen);
	switch (result) {
		/* entry okay as is */
	case FSCACHE_CHECKAUX_OKAY:
		fscache_stat(&fscache_n_checkaux_okay);
		break;

		/* entry requires update */
	case FSCACHE_CHECKAUX_NEEDS_UPDATE:
		fscache_stat(&fscache_n_checkaux_update);
		break;

		/* entry requires deletion */
	case FSCACHE_CHECKAUX_OBSOLETE:
		fscache_stat(&fscache_n_checkaux_obsolete);
		break;

	default:
		BUG();
	}

	return result;
}