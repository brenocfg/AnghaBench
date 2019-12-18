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
typedef  char* uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int _decode_uleb128 (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static uint8_t *
dump_unknown_tag(uint64_t tag, uint8_t *p, uint8_t *pe)
{
	uint64_t val;

	/*
	 * According to ARM EABI: For tags > 32, even numbered tags have
	 * a ULEB128 param and odd numbered ones have NUL-terminated
	 * string param. This rule probably also applies for tags <= 32
	 * if the object arch is not ARM.
	 */

	printf("  Tag_unknown_%ju: ", (uintmax_t) tag);

	if (tag & 1) {
		printf("%s\n", (char *) p);
		p += strlen((char *) p) + 1;
	} else {
		val = _decode_uleb128(&p, pe);
		printf("%ju\n", (uintmax_t) val);
	}

	return (p);
}