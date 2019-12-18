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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
#define  Tag_GNU_Power_ABI_FP 129 
#define  Tag_GNU_Power_ABI_Vector 128 
 int _decode_uleb128 (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dump_compatibility_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dump_unknown_tag (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ppc_abi_fp (int) ; 
 char* ppc_abi_vector (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
dump_ppc_attributes(uint8_t *p, uint8_t *pe)
{
	uint64_t tag, val;

	while (p < pe) {
		tag = _decode_uleb128(&p, pe);
		switch (tag) {
		case Tag_GNU_Power_ABI_FP:
			val = _decode_uleb128(&p, pe);
			printf("  Tag_GNU_Power_ABI_FP: %s\n", ppc_abi_fp(val));
			break;
		case Tag_GNU_Power_ABI_Vector:
			val = _decode_uleb128(&p, pe);
			printf("  Tag_GNU_Power_ABI_Vector: %s\n",
			    ppc_abi_vector(val));
			break;
		case 32:	/* Tag_compatibility */
			p = dump_compatibility_tag(p, pe);
			break;
		default:
			p = dump_unknown_tag(tag, p, pe);
			break;
		}
	}
}