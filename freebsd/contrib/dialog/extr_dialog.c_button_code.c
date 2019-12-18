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
typedef  int /*<<< orphan*/  table ;

/* Variables and functions */
#define  DLG_EXIT_CANCEL 131 
 int DLG_EXIT_ERROR ; 
#define  DLG_EXIT_EXTRA 130 
#define  DLG_EXIT_HELP 129 
#define  DLG_EXIT_OK 128 
 int /*<<< orphan*/  Usage (char*) ; 
 int /*<<< orphan*/  dlg_strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static int
button_code(const char *name)
{
    /* *INDENT-OFF* */
    static struct {
	const char *name;
	int code;
    } table[] = {
	{ "ok",	    DLG_EXIT_OK },
	{ "yes",    DLG_EXIT_OK },
	{ "cancel", DLG_EXIT_CANCEL },
	{ "no",	    DLG_EXIT_CANCEL },
	{ "help",   DLG_EXIT_HELP },
	{ "extra",  DLG_EXIT_EXTRA },
    };
    /* *INDENT-ON* */

    int code = DLG_EXIT_ERROR;
    size_t i;

    for (i = 0; i < (sizeof(table) / sizeof(table[0])); i++) {
	if (!dlg_strcmp(name, table[i].name)) {
	    code = table[i].code;
	    break;
	}
    }

    if (code == DLG_EXIT_ERROR) {
	char temp[80];
	sprintf(temp, "Button name \"%.20s\" unknown", name);
	Usage(temp);
    }

    return code;
}