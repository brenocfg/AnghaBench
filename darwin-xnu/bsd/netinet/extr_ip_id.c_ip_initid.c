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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  bitstr_t ;

/* Variables and functions */
 int ARRAY_SIZE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CASSERT (int) ; 
 int /*<<< orphan*/  _FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int bitstr_size (int) ; 
 int /*<<< orphan*/ * id_array ; 
 int /*<<< orphan*/ * id_bits ; 
 int /*<<< orphan*/  ipid_lock ; 
 int /*<<< orphan*/  ipid_lock_attr ; 
 int /*<<< orphan*/  ipid_lock_grp ; 
 int /*<<< orphan*/  ipid_lock_grp_attr ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ip_initid(void)
{
	VERIFY(id_array == NULL);
	VERIFY(id_bits == NULL);

	_CASSERT(ARRAY_SIZE >= 512 && ARRAY_SIZE <= 32768);

	ipid_lock_grp_attr  = lck_grp_attr_alloc_init();
	ipid_lock_grp = lck_grp_alloc_init("ipid", ipid_lock_grp_attr);
	ipid_lock_attr = lck_attr_alloc_init();
	lck_mtx_init(&ipid_lock, ipid_lock_grp, ipid_lock_attr);

	id_array = (uint16_t *)_MALLOC(ARRAY_SIZE * sizeof (uint16_t),
	    M_TEMP, M_WAITOK | M_ZERO);
	id_bits = (bitstr_t *)_MALLOC(bitstr_size(65536), M_TEMP,
	    M_WAITOK | M_ZERO);
	if (id_array == NULL || id_bits == NULL) {
		/* Just in case; neither or both. */
		if (id_array != NULL) {
			_FREE(id_array, M_TEMP);
			id_array = NULL;
		}
		if (id_bits != NULL) {
			_FREE(id_bits, M_TEMP);
			id_bits = NULL;
		}
	}
}