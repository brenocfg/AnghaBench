#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  discordPresence ;
struct TYPE_4__ {char* state; char* details; char* largeImageKey; char* smallImageKey; char* partyId; int partySize; int partyMax; char* matchSecret; char* joinSecret; char* spectateSecret; scalar_t__ instance; scalar_t__ endTimestamp; int /*<<< orphan*/  startTimestamp; } ;
typedef  TYPE_1__ DiscordRichPresence ;

/* Variables and functions */
 int /*<<< orphan*/  Discord_ClearPresence () ; 
 int /*<<< orphan*/  Discord_UpdatePresence (TYPE_1__*) ; 
 int FrustrationLevel ; 
 scalar_t__ SendPresence ; 
 int /*<<< orphan*/  StartTime ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void updateDiscordPresence()
{
    if (SendPresence) {
        char buffer[256];
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = "West of House";
        sprintf(buffer, "Frustration level: %d", FrustrationLevel);
        discordPresence.details = buffer;
        discordPresence.startTimestamp = StartTime;
        discordPresence.endTimestamp = time(0) + 5 * 60;
        discordPresence.largeImageKey = "canary-large";
        discordPresence.smallImageKey = "ptb-small";
        discordPresence.partyId = "party1234";
        discordPresence.partySize = 1;
        discordPresence.partyMax = 6;
        discordPresence.matchSecret = "xyzzy";
        discordPresence.joinSecret = "join";
        discordPresence.spectateSecret = "look";
        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    }
    else {
        Discord_ClearPresence();
    }
}