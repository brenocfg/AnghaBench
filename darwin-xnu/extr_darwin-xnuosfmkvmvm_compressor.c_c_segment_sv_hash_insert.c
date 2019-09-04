#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct c_sv_hash_entry {int he_data; scalar_t__ he_ref; scalar_t__ he_record; } ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  UInt64 ;
struct TYPE_2__ {scalar_t__ he_record; } ;

/* Variables and functions */
 int C_SV_HASH_MASK ; 
 int C_SV_HASH_MAX_MISS ; 
 int C_SV_HASH_SIZE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 scalar_t__ OSCompareAndSwap64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 TYPE_1__* c_segment_sv_hash_table ; 
 int /*<<< orphan*/  c_segment_svp_in_hash ; 
 int /*<<< orphan*/  c_segment_svp_nonzero_compressions ; 
 int /*<<< orphan*/  c_segment_svp_zero_compressions ; 

__attribute__((used)) static int
c_segment_sv_hash_insert(uint32_t data)
{
	int		hash_sindx;
	int		misses;
	struct c_sv_hash_entry o_sv_he, n_sv_he;
	boolean_t	got_ref = FALSE;

	if (data == 0)
		OSAddAtomic(1, &c_segment_svp_zero_compressions);
	else
		OSAddAtomic(1, &c_segment_svp_nonzero_compressions);

	hash_sindx = data & C_SV_HASH_MASK;
	
	for (misses = 0; misses < C_SV_HASH_MAX_MISS; misses++)
	{
		o_sv_he.he_record = c_segment_sv_hash_table[hash_sindx].he_record;

		while (o_sv_he.he_data == data || o_sv_he.he_ref == 0) {
			n_sv_he.he_ref = o_sv_he.he_ref + 1;
			n_sv_he.he_data = data;

			if (OSCompareAndSwap64((UInt64)o_sv_he.he_record, (UInt64)n_sv_he.he_record, (UInt64 *) &c_segment_sv_hash_table[hash_sindx].he_record) == TRUE) {
				if (n_sv_he.he_ref == 1)
					OSAddAtomic(1, &c_segment_svp_in_hash);
				got_ref = TRUE;
				break;
			}
			o_sv_he.he_record = c_segment_sv_hash_table[hash_sindx].he_record;
		}
		if (got_ref == TRUE)
			break;
		hash_sindx++;

		if (hash_sindx == C_SV_HASH_SIZE)
			hash_sindx = 0;
	}
	if (got_ref == FALSE)
		return(-1);

	return (hash_sindx);
}