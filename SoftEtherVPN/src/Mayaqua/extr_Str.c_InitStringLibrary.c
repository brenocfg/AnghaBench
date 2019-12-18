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
 int /*<<< orphan*/  Alert (char*,int /*<<< orphan*/ *) ; 
 int CheckStringLibrary () ; 
 int /*<<< orphan*/  InitInternational () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token_lock ; 

void InitStringLibrary()
{
	// Create a lock for token
	token_lock = NewLock();

	// Initialization of the International Library
	InitInternational();

	// Operation check
	if (CheckStringLibrary() == false)
	{
#ifdef	OS_WIN32
		Alert("String Library Init Failed.\r\nPlease check your locale settings.", NULL);
#else	// OS_WIN32
		Alert("String Library Init Failed.\r\nPlease check your locale settings and iconv() libraries.", NULL);
#endif	// OS_WIN32
		exit(0);
	}
}