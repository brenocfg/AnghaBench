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
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ e_machine; } ;
struct readelf {TYPE_1__ ehdr; } ;

/* Variables and functions */
 scalar_t__ EM_X86_64 ; 
 size_t GNU_PROPERTY_HIPROC ; 
 size_t GNU_PROPERTY_LOPROC ; 
#define  GNU_PROPERTY_X86_FEATURE_1_AND 128 
 int /*<<< orphan*/  dump_flags (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  gnu_property_x86_feature_1_and_bits ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ roundup2 (size_t,int) ; 

__attribute__((used)) static void
dump_gnu_property_type_0(struct readelf *re, const char *buf, size_t sz)
{
	size_t i;
	uint32_t type, prop_sz;

	printf("      Properties: ");
	while (sz > 0) {
		if (sz < 8)
			goto bad;

		type = *(const uint32_t *)(const void *)buf;
		prop_sz = *(const uint32_t *)(const void *)(buf + 4);
		buf += 8;
		sz -= 8;

		if (prop_sz > sz)
			goto bad;

		if (type >= GNU_PROPERTY_LOPROC &&
		    type <= GNU_PROPERTY_HIPROC) {
			if (re->ehdr.e_machine != EM_X86_64) {
				printf("machine type %x unknown\n",
				    re->ehdr.e_machine);
				goto unknown;
			}
			switch (type) {
			case GNU_PROPERTY_X86_FEATURE_1_AND:
				printf("x86 features:");
				if (prop_sz != 4)
					goto bad;
				dump_flags(gnu_property_x86_feature_1_and_bits,
				    *(const uint32_t *)(const void *)buf);
				break;
			}
		}

		buf += roundup2(prop_sz, 8);
		sz -= roundup2(prop_sz, 8);
	}
	return;
bad:
	printf("corrupt GNU property\n");
unknown:
	printf("remaining description data:");
	for (i = 0; i < sz; i++)
		printf(" %02x", (unsigned char)buf[i]);
	printf("\n");
}