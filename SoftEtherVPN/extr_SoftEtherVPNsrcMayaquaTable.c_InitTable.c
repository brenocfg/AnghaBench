#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  table_name ;
struct TYPE_9__ {int /*<<< orphan*/  Name; int /*<<< orphan*/ * LcidList; int /*<<< orphan*/  LangList; } ;
struct TYPE_8__ {int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ LANGLIST ;

/* Variables and functions */
 int /*<<< orphan*/  Alert (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLangList (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetBestLangByName (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* GetBestLangForCurrentEnvironment (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadLangConfigCurrentDir (char*,int) ; 
 int /*<<< orphan*/ * LoadLangList () ; 
 int LoadTable (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ MayaquaIsMinimalMode () ; 
 int /*<<< orphan*/  SaveLangConfigCurrentDir (int /*<<< orphan*/ ) ; 
 TYPE_2__ current_lang ; 
 TYPE_2__ current_os_lang ; 
 int /*<<< orphan*/  exit (int) ; 

void InitTable()
{
	LIST *o;
	char tmp[MAX_SIZE];
	LANGLIST *e = NULL;
	LANGLIST *os_lang = NULL;
	char table_name[MAX_SIZE];
	if (MayaquaIsMinimalMode())
	{
		// Not to load in case of minimum mode
		return;
	}

	o = LoadLangList();
	if (o == NULL)
	{
LABEL_FATAL_ERROR:
		Alert("Fatal Error: The file \"hamcore.se2\" is missing or broken.\r\nPlease check hamcore.se2.\r\n\r\n(First, reboot the computer. If this problem occurs again, please reinstall VPN software files.)", NULL);
		exit(-1);
		return;
	}

	// Read the lang.config
	if (LoadLangConfigCurrentDir(tmp, sizeof(tmp)))
	{
		e = GetBestLangByName(o, tmp);
	}

	os_lang = GetBestLangForCurrentEnvironment(o);

	if (e == NULL)
	{
		e = os_lang;
	}

	if (e == NULL)
	{
		goto LABEL_FATAL_ERROR;
	}

	SaveLangConfigCurrentDir(e->Name);

	Copy(&current_lang, e, sizeof(LANGLIST));
	Copy(&current_os_lang, os_lang, sizeof(LANGLIST));

	current_lang.LangList = current_lang.LcidList = NULL;
	current_os_lang.LangList = current_os_lang.LcidList = NULL;

	// Read the corresponding string table
	Format(table_name, sizeof(table_name), "|strtable_%s.stb", current_lang.Name);
	if (LoadTable(table_name) == false)
	{
		goto LABEL_FATAL_ERROR;
	}

	FreeLangList(o);
}