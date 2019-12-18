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
typedef  scalar_t__ i2eBordStrPtr ;

/* Variables and functions */
 int IP2_MAX_BOARDS ; 
 scalar_t__* i2BoardPtrTable ; 
 int /*<<< orphan*/  i2ServiceBoard (scalar_t__) ; 

__attribute__((used)) static inline void
service_all_boards(void)
{
	int i;
	i2eBordStrPtr  pB;

	/* Service every board on the list */
	for( i = 0; i < IP2_MAX_BOARDS; ++i ) {
		pB = i2BoardPtrTable[i];
		if ( pB ) {
			i2ServiceBoard( pB );
		}
	}
}