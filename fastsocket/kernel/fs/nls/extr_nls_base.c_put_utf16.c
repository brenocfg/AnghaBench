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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  enum utf16_endian { ____Placeholder_utf16_endian } utf16_endian ;

/* Variables and functions */
#define  UTF16_BIG_ENDIAN 129 
#define  UTF16_LITTLE_ENDIAN 128 
 int /*<<< orphan*/  __cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  __cpu_to_le16 (unsigned int) ; 

__attribute__((used)) static inline void put_utf16(wchar_t *s, unsigned c, enum utf16_endian endian)
{
	switch (endian) {
	default:
		*s = (wchar_t) c;
		break;
	case UTF16_LITTLE_ENDIAN:
		*s = __cpu_to_le16(c);
		break;
	case UTF16_BIG_ENDIAN:
		*s = __cpu_to_be16(c);
		break;
	}
}