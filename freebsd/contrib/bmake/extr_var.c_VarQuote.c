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
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int,char const*) ; 
 char* Buf_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 char* Shell_GetNewline () ; 
 int /*<<< orphan*/  VAR ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ismeta (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
VarQuote(char *str, Boolean quoteDollar)
{

    Buffer  	  buf;
    const char	*newline;
    size_t nlen;

    if ((newline = Shell_GetNewline()) == NULL)
	    newline = "\\\n";
    nlen = strlen(newline);

    Buf_Init(&buf, 0);

    for (; *str != '\0'; str++) {
	if (*str == '\n') {
	    Buf_AddBytes(&buf, nlen, newline);
	    continue;
	}
	if (isspace((unsigned char)*str) || ismeta((unsigned char)*str))
	    Buf_AddByte(&buf, '\\');
	Buf_AddByte(&buf, *str);
	if (quoteDollar && *str == '$')
	    Buf_AddBytes(&buf, 2, "\\$");
    }

    str = Buf_Destroy(&buf, FALSE);
    if (DEBUG(VAR))
	fprintf(debug_file, "QuoteMeta: [%s]\n", str);
    return str;
}