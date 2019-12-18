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
struct TYPE_3__ {char* P_ptr; char* P_end; int /*<<< orphan*/  lineno; int /*<<< orphan*/ * nextbuf; } ;
typedef  TYPE_1__ IFile ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_FATAL ; 
 int PARSE_RAW ; 
 int PARSE_SKIP ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* curFile ; 
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static char *
ParseGetLine(int flags, int *length)
{
    IFile *cf = curFile;
    char *ptr;
    char ch;
    char *line;
    char *line_end;
    char *escaped;
    char *comment;
    char *tp;

    /* Loop through blank lines and comment lines */
    for (;;) {
	cf->lineno++;
	line = cf->P_ptr;
	ptr = line;
	line_end = line;
	escaped = NULL;
	comment = NULL;
	for (;;) {
	    if (cf->P_end != NULL && ptr == cf->P_end) {
		/* end of buffer */
		ch = 0;
		break;
	    }
	    ch = *ptr;
	    if (ch == 0 || (ch == '\\' && ptr[1] == 0)) {
		if (cf->P_end == NULL)
		    /* End of string (aka for loop) data */
		    break;
		/* see if there is more we can parse */
		while (ptr++ < cf->P_end) {
		    if ((ch = *ptr) == '\n') {
			if (ptr > line && ptr[-1] == '\\')
			    continue;
			Parse_Error(PARSE_WARNING,
			    "Zero byte read from file, skipping rest of line.");
			break;
		    }
		}
		if (cf->nextbuf != NULL) {
		    /*
		     * End of this buffer; return EOF and outer logic
		     * will get the next one. (eww)
		     */
		    break;
		}
		Parse_Error(PARSE_FATAL, "Zero byte read from file");
		return NULL;
	    }

	    if (ch == '\\') {
		/* Don't treat next character as special, remember first one */
		if (escaped == NULL)
		    escaped = ptr;
		if (ptr[1] == '\n')
		    cf->lineno++;
		ptr += 2;
		line_end = ptr;
		continue;
	    }
	    if (ch == '#' && comment == NULL) {
		/* Remember first '#' for comment stripping */
		/* Unless previous char was '[', as in modifier :[#] */
		if (!(ptr > line && ptr[-1] == '['))
		    comment = line_end;
	    }
	    ptr++;
	    if (ch == '\n')
		break;
	    if (!isspace((unsigned char)ch))
		/* We are not interested in trailing whitespace */
		line_end = ptr;
	}

	/* Save next 'to be processed' location */
	cf->P_ptr = ptr;

	/* Check we have a non-comment, non-blank line */
	if (line_end == line || comment == line) {
	    if (ch == 0)
		/* At end of file */
		return NULL;
	    /* Parse another line */
	    continue;
	}

	/* We now have a line of data */
	*line_end = 0;

	if (flags & PARSE_RAW) {
	    /* Leave '\' (etc) in line buffer (eg 'for' lines) */
	    *length = line_end - line;
	    return line;
	}

	if (flags & PARSE_SKIP) {
	    /* Completely ignore non-directives */
	    if (line[0] != '.')
		continue;
	    /* We could do more of the .else/.elif/.endif checks here */
	}
	break;
    }

    /* Brutally ignore anything after a non-escaped '#' in non-commands */
    if (comment != NULL && line[0] != '\t') {
	line_end = comment;
	*line_end = 0;
    }

    /* If we didn't see a '\\' then the in-situ data is fine */
    if (escaped == NULL) {
	*length = line_end - line;
	return line;
    }

    /* Remove escapes from '\n' and '#' */
    tp = ptr = escaped;
    escaped = line;
    for (; ; *tp++ = ch) {
	ch = *ptr++;
	if (ch != '\\') {
	    if (ch == 0)
		break;
	    continue;
	}

	ch = *ptr++;
	if (ch == 0) {
	    /* Delete '\\' at end of buffer */
	    tp--;
	    break;
	}

	if (ch == '#' && line[0] != '\t')
	    /* Delete '\\' from before '#' on non-command lines */
	    continue;

	if (ch != '\n') {
	    /* Leave '\\' in buffer for later */
	    *tp++ = '\\';
	    /* Make sure we don't delete an escaped ' ' from the line end */
	    escaped = tp + 1;
	    continue;
	}

	/* Escaped '\n' replace following whitespace with a single ' ' */
	while (ptr[0] == ' ' || ptr[0] == '\t')
	    ptr++;
	ch = ' ';
    }

    /* Delete any trailing spaces - eg from empty continuations */
    while (tp > escaped && isspace((unsigned char)tp[-1]))
	tp--;

    *tp = 0;
    *length = tp - line;
    return line;
}