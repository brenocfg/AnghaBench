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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CARDIO_ERROR_INTERNAL ; 
 int /*<<< orphan*/  CARDIO_ERROR_NOCARD ; 
 int /*<<< orphan*/  CARDIO_ERROR_READY ; 
 int CARDIO_OP_IOERR_ADDR ; 
 int CARDIO_OP_IOERR_CRC ; 
 int CARDIO_OP_IOERR_FATAL ; 
 int CARDIO_OP_IOERR_IDLE ; 
 int CARDIO_OP_IOERR_ILL ; 
 int CARDIO_OP_IOERR_PARAM ; 
 scalar_t__ INITIALIZING ; 
 size_t MAX_DRIVE ; 
 int MMC_ERROR_ADDRESS ; 
 int MMC_ERROR_CRC ; 
 int MMC_ERROR_IDLE ; 
 int MMC_ERROR_ILL ; 
 int MMC_ERROR_PARAM ; 
 int* _ioError ; 
 scalar_t__* _ioFlag ; 

__attribute__((used)) static __inline__ u32 __check_response(s32 drv_no,u8 res)
{
	if(drv_no<0 || drv_no>=MAX_DRIVE) return CARDIO_ERROR_NOCARD;

	_ioError[drv_no] = 0;
	if(_ioFlag[drv_no]==INITIALIZING && res&MMC_ERROR_IDLE) {
		_ioError[drv_no] |= CARDIO_OP_IOERR_IDLE;
		return CARDIO_ERROR_READY;
	} else {
		if(res&MMC_ERROR_PARAM) _ioError[drv_no] |= CARDIO_OP_IOERR_PARAM;
		if(res&MMC_ERROR_ADDRESS) _ioError[drv_no] |= CARDIO_OP_IOERR_ADDR;
		if(res&MMC_ERROR_CRC) _ioError[drv_no] |= CARDIO_OP_IOERR_CRC;
		if(res&MMC_ERROR_ILL) _ioError[drv_no] |= CARDIO_OP_IOERR_ILL;
	}
	return ((_ioError[drv_no]&CARDIO_OP_IOERR_FATAL)?CARDIO_ERROR_INTERNAL:CARDIO_ERROR_READY);
}