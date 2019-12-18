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
 int /*<<< orphan*/  RARCH_LOG (char*,int,char const*) ; 

__attribute__((used)) static void handle_discord_error(int errcode, const char* message)
{
   RARCH_LOG("[discord] error (%d: %s)\n", errcode, message);
}