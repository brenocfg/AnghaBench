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
 int /*<<< orphan*/  ConfigDevice (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  FCFGD_GAMEPAD ; 
 int /*<<< orphan*/  FCFGD_HYPERSHOT ; 
 int /*<<< orphan*/  FCFGD_POWERPAD ; 
 int /*<<< orphan*/  FCFGD_QUIZKING ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,size_t) ; 

__attribute__((used)) static void InputCfg(char *text)
{
         if(!strncasecmp(text,"gamepad",strlen("gamepad")))
         {
          ConfigDevice(FCFGD_GAMEPAD,(text[strlen("gamepad")]-'1')&3);
         }
         else if(!strncasecmp(text,"powerpad",strlen("powerpad")))
         {
          ConfigDevice(FCFGD_POWERPAD,(text[strlen("powerpad")]-'1')&1);
         }
         else if(!strcasecmp(text,"hypershot"))
          ConfigDevice(FCFGD_HYPERSHOT,0);
         else if(!strcasecmp(text,"quizking"))
          ConfigDevice(FCFGD_QUIZKING,0);
}