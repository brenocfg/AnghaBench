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
struct TYPE_3__ {scalar_t__ _key; scalar_t__ _value; } ;
typedef  TYPE_1__ unicode_mappings16 ;
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */

__attribute__((used)) static inline u_int16_t
getmappedvalue16(const unicode_mappings16 *theTable, u_int32_t numElem,
		u_int16_t character)
{
	const unicode_mappings16 *p, *q, *divider;

	if ((character < theTable[0]._key) || (character > theTable[numElem-1]._key))
		return (0);

	p = theTable;
	q = p + (numElem-1);
	while (p <= q) {
		divider = p + ((q - p) >> 1);	/* divide by 2 */
		if (character < divider->_key)
			q = divider - 1;
		else if (character > divider->_key)
			p = divider + 1;
		else
			return (divider->_value);
	}
	return (0);
}