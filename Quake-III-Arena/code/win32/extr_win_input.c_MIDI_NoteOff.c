#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sysMsgTime; } ;

/* Variables and functions */
 int K_AUX1 ; 
 int /*<<< orphan*/  SE_KEY ; 
 int /*<<< orphan*/  Sys_QueEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ g_wv ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void MIDI_NoteOff( int note )
{
	int qkey;

	qkey = note - 60 + K_AUX1;

	if ( qkey > 255 || qkey < K_AUX1 )
		return;

	Sys_QueEvent( g_wv.sysMsgTime, SE_KEY, qkey, qfalse, 0, NULL );
}