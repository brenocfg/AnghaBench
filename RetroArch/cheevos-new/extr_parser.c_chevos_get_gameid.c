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
typedef  int /*<<< orphan*/  gameid ;

/* Variables and functions */
 int /*<<< orphan*/  CHEEVOS_JSON_KEY_GAMEID ; 
 scalar_t__ rcheevos_get_value (char const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

unsigned chevos_get_gameid(const char* json)
{
   char gameid[32];

   if (rcheevos_get_value(json, CHEEVOS_JSON_KEY_GAMEID, gameid, sizeof(gameid)) != 0)
      return 0;

   return (unsigned)strtol(gameid, NULL, 10);
}