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
typedef  int /*<<< orphan*/  GameInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CDCORE_ISO ; 
 int /*<<< orphan*/  Cs2DeInit () ; 
 int /*<<< orphan*/  Cs2GetIP (int) ; 
 int /*<<< orphan*/  Cs2Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cdip ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int GameInfoFromPath(const char * filename, GameInfo * info)
{
   if (cdip != NULL) return 0;

   Cs2Init(0, CDCORE_ISO, filename, NULL, NULL, NULL);
   Cs2GetIP(1);

   memcpy(info, cdip, sizeof(GameInfo));

   Cs2DeInit();

   return 1;
}