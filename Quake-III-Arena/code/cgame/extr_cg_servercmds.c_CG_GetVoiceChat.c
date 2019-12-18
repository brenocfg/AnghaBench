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
struct TYPE_5__ {int numVoiceChats; TYPE_1__* voiceChats; } ;
typedef  TYPE_2__ voiceChatList_t ;
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_4__ {int numSounds; char** chats; int /*<<< orphan*/ * sounds; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 
 int random () ; 

int CG_GetVoiceChat( voiceChatList_t *voiceChatList, const char *id, sfxHandle_t *snd, char **chat) {
	int i, rnd;

	for ( i = 0; i < voiceChatList->numVoiceChats; i++ ) {
		if ( !Q_stricmp( id, voiceChatList->voiceChats[i].id ) ) {
			rnd = random() * voiceChatList->voiceChats[i].numSounds;
			*snd = voiceChatList->voiceChats[i].sounds[rnd];
			*chat = voiceChatList->voiceChats[i].chats[rnd];
			return qtrue;
		}
	}
	return qfalse;
}