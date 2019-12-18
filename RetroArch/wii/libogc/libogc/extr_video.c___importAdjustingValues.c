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
struct TYPE_3__ {scalar_t__ display_offsetH; } ;
typedef  TYPE_1__ syssram ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 scalar_t__ CONF_GetDisplayOffsetH (scalar_t__*) ; 
 TYPE_1__* __SYS_LockSram () ; 
 int /*<<< orphan*/  __SYS_UnlockSram (int /*<<< orphan*/ ) ; 
 scalar_t__ displayOffsetH ; 
 scalar_t__ displayOffsetV ; 

__attribute__((used)) static inline void __importAdjustingValues()
{
#ifdef HW_DOL
	syssram *sram;

	sram = __SYS_LockSram();
	displayOffsetH = sram->display_offsetH;
	__SYS_UnlockSram(0);
#else
	s8 offset;
	if ( CONF_GetDisplayOffsetH(&offset) == 0 ) {
		displayOffsetH = offset;
	} else {
		displayOffsetH = 0;
	}
#endif
	displayOffsetV = 0;
}