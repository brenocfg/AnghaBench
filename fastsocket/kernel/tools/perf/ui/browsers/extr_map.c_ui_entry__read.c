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
struct newtExitStruct {int dummy; } ;
typedef  int /*<<< orphan*/ * newtComponent ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL (char) ; 
 int /*<<< orphan*/  NEWT_FLAG_SCROLL ; 
 int /*<<< orphan*/  NEWT_KEY_ENTER ; 
 int /*<<< orphan*/  NEWT_KEY_ESCAPE ; 
 int /*<<< orphan*/  NEWT_KEY_LEFT ; 
 int /*<<< orphan*/  newtCenteredWindow (int,int,char const*) ; 
 int /*<<< orphan*/ * newtEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newtForm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newtFormAddComponent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newtFormAddHotKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newtFormDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newtFormRun (int /*<<< orphan*/ *,struct newtExitStruct*) ; 
 int /*<<< orphan*/  newtPopWindow () ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int ui_entry__read(const char *title, char *bf, size_t size, int width)
{
	struct newtExitStruct es;
	newtComponent form, entry;
	const char *result;
	int err = -1;

	newtCenteredWindow(width, 1, title);
	form = newtForm(NULL, NULL, 0);
	if (form == NULL)
		return -1;

	entry = newtEntry(0, 0, "0x", width, &result, NEWT_FLAG_SCROLL);
	if (entry == NULL)
		goto out_free_form;

	newtFormAddComponent(form, entry);
	newtFormAddHotKey(form, NEWT_KEY_ENTER);
	newtFormAddHotKey(form, NEWT_KEY_ESCAPE);
	newtFormAddHotKey(form, NEWT_KEY_LEFT);
	newtFormAddHotKey(form, CTRL('c'));
	newtFormRun(form, &es);

	if (result != NULL) {
		strncpy(bf, result, size);
		err = 0;
	}
out_free_form:
	newtPopWindow();
	newtFormDestroy(form);
	return err;
}