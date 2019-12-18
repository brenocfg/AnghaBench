#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UPDATE_NOTIFY_PROC ;
typedef  int /*<<< orphan*/  UPDATE_ISFOREGROUND_PROC ;
typedef  int /*<<< orphan*/  UPDATE_CLIENT_SETTING ;
struct TYPE_5__ {int /*<<< orphan*/  Thread; int /*<<< orphan*/  HaltEvent; void* Param; int /*<<< orphan*/  Setting; int /*<<< orphan*/  MyLanguage; int /*<<< orphan*/  MyDate; scalar_t__ MyBuild; int /*<<< orphan*/  SoftwareTitle; int /*<<< orphan*/  SoftwareName; int /*<<< orphan*/  FamilyName; int /*<<< orphan*/  ClientId; int /*<<< orphan*/ * IsForegroundCb; int /*<<< orphan*/ * Callback; } ;
typedef  TYPE_1__ UPDATE_CLIENT ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateClientThreadProc ; 
 TYPE_1__* ZeroMalloc (int) ; 

UPDATE_CLIENT *NewUpdateClient(UPDATE_NOTIFY_PROC *cb, UPDATE_ISFOREGROUND_PROC *isforeground_cb, void *param, char *family_name, char *software_name, wchar_t *software_title, UINT my_build, UINT64 my_date, char *my_lang, UPDATE_CLIENT_SETTING *current_setting, char *client_id)
{
	UPDATE_CLIENT *c;
	// Validate arguments
	if (family_name == NULL || software_title == NULL || software_name == NULL || my_build == 0 ||
		my_lang == NULL || current_setting == NULL || cb == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(UPDATE_CLIENT));

	c->Callback = cb;
	c->IsForegroundCb = isforeground_cb;

	StrCpy(c->ClientId, sizeof(c->ClientId), client_id);
	StrCpy(c->FamilyName, sizeof(c->FamilyName), family_name);
	StrCpy(c->SoftwareName, sizeof(c->SoftwareName), software_name);
	UniStrCpy(c->SoftwareTitle, sizeof(c->SoftwareTitle), software_title);
	c->MyBuild = my_build;
	c->MyDate = my_date;
	StrCpy(c->MyLanguage, sizeof(c->MyLanguage), my_lang);

	Copy(&c->Setting, current_setting, sizeof(c->Setting));

	c->Param = param;

	c->HaltEvent = NewEvent();

	// Create a thread
	c->Thread = NewThread(UpdateClientThreadProc, c);

	return c;
}