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
typedef  int u_int32_t ;
struct secpolicy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_SADB_LOCKED ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 struct secpolicy* __key_getspbyid (int) ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_freesp (struct secpolicy*,int /*<<< orphan*/ ) ; 
 int key_spi_trycnt ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int policy_id ; 
 int /*<<< orphan*/  sadb_mutex ; 

__attribute__((used)) static u_int32_t
key_getnewspid(void)
{
	u_int32_t newid = 0;
	int count = key_spi_trycnt;	/* XXX */
	struct secpolicy *sp;
	
	/* when requesting to allocate spi ranged */
	lck_mtx_lock(sadb_mutex);
	while (count--) {
		newid = (policy_id = (policy_id == ~0 ? 1 : policy_id + 1));
		
		if ((sp = __key_getspbyid(newid)) == NULL)
			break;
		
		key_freesp(sp, KEY_SADB_LOCKED);
	}
	lck_mtx_unlock(sadb_mutex);
	if (count == 0 || newid == 0) {
		ipseclog((LOG_DEBUG, "key_getnewspid: to allocate policy id is failed.\n"));
		return 0;
	}
	
	return newid;
}