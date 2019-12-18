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
typedef  int /*<<< orphan*/  cmd ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  EnableProbe (int) ; 
 int /*<<< orphan*/  FreeCedar () ; 
 int /*<<< orphan*/  FreeMayaqua () ; 
 int /*<<< orphan*/  InitCedar () ; 
 int /*<<< orphan*/  InitMayaqua (int,int,int,char**) ; 
 int /*<<< orphan*/  InitProcessCallOnce () ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SetHamMode () ; 
 int /*<<< orphan*/  StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int TestMain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdline ; 

int main(int argc, char *argv[])
{
	bool memchk = false;
	UINT i;
	char cmd[MAX_SIZE];
	char *s;
	int status = 0;

	InitProcessCallOnce();

	cmd[0] = 0;
	if (argc >= 2)
	{
		for (i = 1;i < (UINT)argc;i++)
		{
			s = argv[i];
			if (s[0] == '/')
			{
				if (!StrCmpi(s, "/memcheck"))
				{
					memchk = true;
				}
			}
			else
			{
				StrCpy(cmd, sizeof(cmd), &s[0]);
			}
		}
	}

	InitMayaqua(memchk, true, argc, argv);
	EnableProbe(true);
	InitCedar();
	SetHamMode();
	status = TestMain(cmdline);
	FreeCedar();
	FreeMayaqua();

	return status;
}