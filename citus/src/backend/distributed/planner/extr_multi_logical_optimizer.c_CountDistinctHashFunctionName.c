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
typedef  int Oid ;

/* Variables and functions */
#define  BPCHAROID 132 
 char const* HLL_HASH_ANY_FUNC_NAME ; 
 char const* HLL_HASH_BIGINT_FUNC_NAME ; 
 char const* HLL_HASH_INTEGER_FUNC_NAME ; 
 char const* HLL_HASH_TEXT_FUNC_NAME ; 
#define  INT4OID 131 
#define  INT8OID 130 
#define  TEXTOID 129 
#define  VARCHAROID 128 

__attribute__((used)) static const char *
CountDistinctHashFunctionName(Oid argumentType)
{
	/* resolve hash function name based on input argument type */
	switch (argumentType)
	{
		case INT4OID:
		{
			return HLL_HASH_INTEGER_FUNC_NAME;
		}

		case INT8OID:
		{
			return HLL_HASH_BIGINT_FUNC_NAME;
		}

		case TEXTOID:
		case BPCHAROID:
		case VARCHAROID:
		{
			return HLL_HASH_TEXT_FUNC_NAME;
		}

		default:
		{
			return HLL_HASH_ANY_FUNC_NAME;
		}
	}
}