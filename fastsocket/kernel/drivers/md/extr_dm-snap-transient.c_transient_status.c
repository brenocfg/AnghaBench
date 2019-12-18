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
struct dm_exception_store {scalar_t__ chunk_size; } ;
typedef  int status_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,unsigned long long) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static unsigned transient_status(struct dm_exception_store *store,
				 status_type_t status, char *result,
				 unsigned maxlen)
{
	unsigned sz = 0;

	switch (status) {
	case STATUSTYPE_INFO:
		break;
	case STATUSTYPE_TABLE:
		DMEMIT(" N %llu", (unsigned long long)store->chunk_size);
	}

	return sz;
}