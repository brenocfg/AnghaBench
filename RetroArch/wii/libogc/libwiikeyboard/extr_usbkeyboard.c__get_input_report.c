#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int s32 ;
struct TYPE_3__ {int modifiers; } ;
struct TYPE_4__ {int fd; TYPE_1__ sc_ndata; int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int USB_ReadIntrMsg (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* _kbd ; 
 int /*<<< orphan*/  hId ; 
 int /*<<< orphan*/ * iosAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iosFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static s32 _get_input_report(void)
{
	u8 *buffer = 0;

	if(!_kbd || _kbd->fd==-1) return -1;
	buffer = iosAlloc(hId, 8);

	if (buffer == NULL)
		return -1;

	s32 ret = USB_ReadIntrMsg(_kbd->fd, _kbd->ep, 8, buffer);

	memcpy(&_kbd->sc_ndata, buffer, 8);
	iosFree(hId, buffer);

	_kbd->sc_ndata.modifiers = (_kbd->sc_ndata.modifiers << 8) | (_kbd->sc_ndata.modifiers >> 8);

	return ret;
}