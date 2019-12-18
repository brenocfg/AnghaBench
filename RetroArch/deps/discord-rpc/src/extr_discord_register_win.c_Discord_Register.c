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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  openCommand ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  Discord_RegisterW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int const) ; 

void Discord_Register(const char* applicationId, const char* command)
{
    wchar_t openCommand[1024];
    const wchar_t* wcommand = NULL;
    wchar_t appId[32];

    MultiByteToWideChar(CP_UTF8, 0, applicationId, -1, appId, 32);
    if (command && command[0])
    {
        const int commandBufferLen = 
           sizeof(openCommand) / sizeof(*openCommand);
        MultiByteToWideChar(CP_UTF8, 0, command, -1,
              openCommand, commandBufferLen);
        wcommand = openCommand;
    }

    Discord_RegisterW(appId, wcommand);
}