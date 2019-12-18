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
typedef  size_t iv_index_t ;
typedef  TYPE_1__* ipc_voucher_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {scalar_t__ iv_table_size; size_t* iv_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline iv_index_t
iv_checksum(ipc_voucher_t voucher, boolean_t *emptyp)
{
	iv_index_t c = 0;

	boolean_t empty = TRUE;
	if (0 < voucher->iv_table_size) {
		iv_index_t i = voucher->iv_table_size - 1;
	
		do {
			iv_index_t v = voucher->iv_table[i];
			c = c << 3 | c >> (32 - 3);		/* rotate */
			c = ~c;					/* invert */
			if (0 < v) {
				c += v;				/* add in */
				empty = FALSE;
			}
		} while (0 < i--);
	}
	*emptyp = empty;
	return c;
}