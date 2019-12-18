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
typedef  int /*<<< orphan*/  archlist ;
struct TYPE_3__ {char* member_0; int member_1; int member_2; int /*<<< orphan*/  name; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  const member_3; } ;
typedef  TYPE_1__ NXArchInfo ;

/* Variables and functions */
#define  NX_LittleEndian 128 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const NXArchInfo *
lookup_arch(const char *archstring)
{
	/*
	 * As new architectures are supported by xnu, add a mapping function
	 * without relying on host libraries.
	 */
	static const NXArchInfo archlist[] = {
		{ "x86_64", 0x01000007 /* CPU_TYPE_X86_64 */, 3 /* CPU_SUBTYPE_X86_64_ALL */, NX_LittleEndian, NULL },
		{ "x86_64h", 0x01000007 /* CPU_TYPE_X86_64 */, 8 /* CPU_SUBTYPE_X86_64_H */, NX_LittleEndian, NULL },
		{ "armv7", 12 /* CPU_TYPE_ARM */, 9 /* CPU_SUBTYPE_ARM_V7 */, NX_LittleEndian, NULL },
		{ "armv7s", 12 /* CPU_TYPE_ARM */, 11 /* CPU_SUBTYPE_ARM_V7S */, NX_LittleEndian, NULL },
		{ "armv7k", 12 /* CPU_TYPE_ARM */, 12 /* CPU_SUBTYPE_ARM_V7K */, NX_LittleEndian, NULL },
		{ "arm64", 0x0100000c /* CPU_TYPE_ARM64 */, 0 /* CPU_SUBTYPE_ARM64_ALL */, NX_LittleEndian, NULL },
	};
	unsigned long i;

	for (i=0; i < sizeof(archlist)/sizeof(archlist[0]); i++) {
		if (0 == strcmp(archstring, archlist[i].name)) {
			return &archlist[i];
		}
	}

	return NULL;
}