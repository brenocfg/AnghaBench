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
typedef  int /*<<< orphan*/  strlist_t ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int,char const*) ; 
 int FOR_SUB_ESCAPE_BRACE ; 
 int FOR_SUB_ESCAPE_PAREN ; 
 int for_var_len (char const*) ; 
 int strlen (char const*) ; 
 int strlist_info (int /*<<< orphan*/ *,unsigned int) ; 
 char* strlist_str (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
for_substitute(Buffer *cmds, strlist_t *items, unsigned int item_no, char ech)
{
    const char *item = strlist_str(items, item_no);
    int len;
    char ch;

    /* If there were no escapes, or the only escape is the other variable
     * terminator, then just substitute the full string */
    if (!(strlist_info(items, item_no) &
	    (ech == ')' ? ~FOR_SUB_ESCAPE_BRACE : ~FOR_SUB_ESCAPE_PAREN))) {
	Buf_AddBytes(cmds, strlen(item), item);
	return;
    }

    /* Escape ':', '$', '\\' and 'ech' - removed by :U processing */
    while ((ch = *item++) != 0) {
	if (ch == '$') {
	    len = for_var_len(item);
	    if (len != 0) {
		Buf_AddBytes(cmds, len + 1, item - 1);
		item += len;
		continue;
	    }
	    Buf_AddByte(cmds, '\\');
	} else if (ch == ':' || ch == '\\' || ch == ech)
	    Buf_AddByte(cmds, '\\');
	Buf_AddByte(cmds, ch);
    }
}