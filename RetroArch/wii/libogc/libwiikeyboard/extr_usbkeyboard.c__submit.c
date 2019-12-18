#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  USBKeyboard_eventType ;
struct TYPE_4__ {int /*<<< orphan*/  keyCode; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ USBKeyboard_event ;
struct TYPE_5__ {int /*<<< orphan*/  (* cb ) (TYPE_1__) ;} ;

/* Variables and functions */
 TYPE_3__* _kbd ; 
 int /*<<< orphan*/  stub1 (TYPE_1__) ; 

__attribute__((used)) static void _submit(USBKeyboard_eventType type, u8 code)
{
	if (!_kbd->cb)
		return;

	USBKeyboard_event ev;
	ev.type = type;
	ev.keyCode = code;

	_kbd->cb(ev);
}