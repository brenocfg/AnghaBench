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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  RestoreConsole (void*) ; 
 void* SetConsoleRaw () ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int getch () ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

bool PasswordPrompt(char *password, UINT size)
{
	UINT wp;
	bool escape = false;
	void *console;
	// Validate arguments
	if (password == NULL || size <= 1)
	{
		if (size >= 1)
		{
			password[0] = 0;
		}
		return false;
	}

	wp = 0;

	Zero(password, size);

	console = SetConsoleRaw();

	while (true)
	{
		int c;

#ifdef	OS_WIN32
		c = getch();
#else	// OS_WIN32
		c = getc(stdin);
#endif	// OS_WIN32

		if (c >= 0x20 && c <= 0x7E)
		{
			// Character
			if ((wp + 1) < size)
			{
				password[wp++] = (char)c;
				putc('*', stdout);
			}
		}
		else if (c == 0x03)
		{
			// Break
			exit(0);
		}
		else if (c == 0x04 || c == 0x1a || c == 0x0D || c==0x0A)
		{
			// Exit
			if (c == 0x04 || c == 0x1a)
			{
				escape = true;
			}
			break;
		}
		else if (c == 0xE0)
		{
			// Read one more character
#ifdef	OS_WIN32
			c = getch();
#else	// OS_WIN32
			c = getc(stdin);
#endif	// OS_WIN32
			if (c == 0x4B || c == 0x53)
			{
				// Backspace
				goto BACKSPACE;
			}
		}
		else if (c == 0x08)
		{
BACKSPACE:
			// Backspace
			if (wp >= 1)
			{
				password[--wp] = 0;
				putc(0x08, stdout);
				putc(' ', stdout);
				putc(0x08, stdout);
			}
		}
	}
	Print("\n");

	RestoreConsole(console);

	return (escape ? false : true);
}