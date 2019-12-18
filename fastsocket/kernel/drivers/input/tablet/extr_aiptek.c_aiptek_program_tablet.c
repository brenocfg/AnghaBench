#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ coordinateMode; } ;
struct TYPE_4__ {int modelCode; int odmCode; int firmwareCode; } ;
struct aiptek {scalar_t__ eventCount; int /*<<< orphan*/  diagnostic; TYPE_3__ curSetting; TYPE_2__* inputdev; TYPE_1__ features; } ;
struct TYPE_5__ {int* absmax; scalar_t__* absmin; } ;

/* Variables and functions */
 size_t ABS_PRESSURE ; 
 size_t ABS_X ; 
 size_t ABS_Y ; 
 scalar_t__ AIPTEK_COORDINATE_ABSOLUTE_MODE ; 
 int /*<<< orphan*/  AIPTEK_DIAGNOSTIC_NA ; 
 int aiptek_command (struct aiptek*,int,int) ; 
 int aiptek_query (struct aiptek*,int,int) ; 

__attribute__((used)) static int aiptek_program_tablet(struct aiptek *aiptek)
{
	int ret;
	/* Execute Resolution500LPI */
	if ((ret = aiptek_command(aiptek, 0x18, 0x04)) < 0)
		return ret;

	/* Query getModelCode */
	if ((ret = aiptek_query(aiptek, 0x02, 0x00)) < 0)
		return ret;
	aiptek->features.modelCode = ret & 0xff;

	/* Query getODMCode */
	if ((ret = aiptek_query(aiptek, 0x03, 0x00)) < 0)
		return ret;
	aiptek->features.odmCode = ret;

	/* Query getFirmwareCode */
	if ((ret = aiptek_query(aiptek, 0x04, 0x00)) < 0)
		return ret;
	aiptek->features.firmwareCode = ret;

	/* Query getXextension */
	if ((ret = aiptek_query(aiptek, 0x01, 0x00)) < 0)
		return ret;
	aiptek->inputdev->absmin[ABS_X] = 0;
	aiptek->inputdev->absmax[ABS_X] = ret - 1;

	/* Query getYextension */
	if ((ret = aiptek_query(aiptek, 0x01, 0x01)) < 0)
		return ret;
	aiptek->inputdev->absmin[ABS_Y] = 0;
	aiptek->inputdev->absmax[ABS_Y] = ret - 1;

	/* Query getPressureLevels */
	if ((ret = aiptek_query(aiptek, 0x08, 0x00)) < 0)
		return ret;
	aiptek->inputdev->absmin[ABS_PRESSURE] = 0;
	aiptek->inputdev->absmax[ABS_PRESSURE] = ret - 1;

	/* Depending on whether we are in absolute or relative mode, we will
	 * do a switchToTablet(absolute) or switchToMouse(relative) command.
	 */
	if (aiptek->curSetting.coordinateMode ==
	    AIPTEK_COORDINATE_ABSOLUTE_MODE) {
		/* Execute switchToTablet */
		if ((ret = aiptek_command(aiptek, 0x10, 0x01)) < 0) {
			return ret;
		}
	} else {
		/* Execute switchToMouse */
		if ((ret = aiptek_command(aiptek, 0x10, 0x00)) < 0) {
			return ret;
		}
	}

	/* Enable the macro keys */
	if ((ret = aiptek_command(aiptek, 0x11, 0x02)) < 0)
		return ret;
#if 0
	/* Execute FilterOn */
	if ((ret = aiptek_command(aiptek, 0x17, 0x00)) < 0)
		return ret;
#endif

	/* Execute AutoGainOn */
	if ((ret = aiptek_command(aiptek, 0x12, 0xff)) < 0)
		return ret;

	/* Reset the eventCount, so we track events from last (re)programming
	 */
	aiptek->diagnostic = AIPTEK_DIAGNOSTIC_NA;
	aiptek->eventCount = 0;

	return 0;
}