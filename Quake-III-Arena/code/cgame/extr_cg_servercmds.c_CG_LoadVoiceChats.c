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

/* Variables and functions */
 int /*<<< orphan*/  CG_ParseVoiceChats (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Printf (char*,int) ; 
 int /*<<< orphan*/  MAX_VOICECHATS ; 
 int trap_MemoryRemaining () ; 
 int /*<<< orphan*/ * voiceChatLists ; 

void CG_LoadVoiceChats( void ) {
	int size;

	size = trap_MemoryRemaining();
	CG_ParseVoiceChats( "scripts/female1.voice", &voiceChatLists[0], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/female2.voice", &voiceChatLists[1], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/female3.voice", &voiceChatLists[2], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/male1.voice", &voiceChatLists[3], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/male2.voice", &voiceChatLists[4], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/male3.voice", &voiceChatLists[5], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/male4.voice", &voiceChatLists[6], MAX_VOICECHATS );
	CG_ParseVoiceChats( "scripts/male5.voice", &voiceChatLists[7], MAX_VOICECHATS );
	CG_Printf("voice chat memory size = %d\n", size - trap_MemoryRemaining());
}