#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct secasvar {size_t state; struct secashead* sah; } ;
struct secashead {int /*<<< orphan*/ * savtree; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIST_INSERT_TAIL (int /*<<< orphan*/ *,struct secasvar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secasvar*,int /*<<< orphan*/ ) ; 
 size_t SADB_SASTATE_MATURE ; 
 scalar_t__ __LIST_CHAINED (struct secasvar*) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  secasvar ; 

__attribute__((used)) static int
key_migratesav(struct secasvar *sav,
			   struct secashead *newsah)
{
	if (sav == NULL || newsah == NULL || sav->state != SADB_SASTATE_MATURE) {
		return EINVAL;
	}
	
	/* remove from SA header */
	if (__LIST_CHAINED(sav))
		LIST_REMOVE(sav, chain);
	
	sav->sah = newsah;
	LIST_INSERT_TAIL(&newsah->savtree[SADB_SASTATE_MATURE], sav, secasvar, chain);
	return 0;
}