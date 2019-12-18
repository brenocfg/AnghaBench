#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int widthInChars; } ;
struct TYPE_4__ {int /*<<< orphan*/  keyCatchers; } ;

/* Variables and functions */
 int /*<<< orphan*/  Field_Clear (TYPE_2__*) ; 
 int /*<<< orphan*/  KEYCATCH_MESSAGE ; 
 TYPE_2__ chatField ; 
 int chat_playerNum ; 
 int /*<<< orphan*/  chat_team ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  qtrue ; 

void Con_MessageMode2_f (void) {
	chat_playerNum = -1;
	chat_team = qtrue;
	Field_Clear( &chatField );
	chatField.widthInChars = 25;
	cls.keyCatchers ^= KEYCATCH_MESSAGE;
}