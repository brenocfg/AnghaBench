#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int WriteMode; int HamMode; int /*<<< orphan*/ * pData; int /*<<< orphan*/ * HamBuf; int /*<<< orphan*/  NameW; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ IO ;

/* Variables and functions */
 int /*<<< orphan*/ * GetUnixio4Stdout () ; 
 int /*<<< orphan*/  g_foreground ; 

__attribute__((used)) static IO *GetIO4Stdout()
{
#ifndef UNIX
	return NULL;
#else // UNIX
	static IO IO4Stdout =
	{
		.Name = {0},
		.NameW = {0},
		.pData = NULL,
		.WriteMode = true,
		.HamMode = false,
		.HamBuf = NULL,
	};

	if (!g_foreground)
	{
		return NULL;
	}

	IO4Stdout.pData = GetUnixio4Stdout();

	return &IO4Stdout;
#endif // UNIX
}