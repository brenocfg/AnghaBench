#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEFINE_YYTABLES ; 
 int /*<<< orphan*/  CMD_ENDIF ; 
 int /*<<< orphan*/  CMD_IF_BISON_BRIDGE ; 
 int /*<<< orphan*/  CMD_IF_CPP_ONLY ; 
 int /*<<< orphan*/  CMD_IF_C_ONLY ; 
 int /*<<< orphan*/  CMD_IF_C_OR_CPP ; 
 int /*<<< orphan*/  CMD_IF_NOT_BISON_BRIDGE ; 
 int /*<<< orphan*/  CMD_IF_NOT_REENTRANT ; 
 int /*<<< orphan*/  CMD_IF_REENTRANT ; 
 int /*<<< orphan*/  CMD_IF_TABLES_SER ; 
 int /*<<< orphan*/  CMD_NOT_FOR_HEADER ; 
 int /*<<< orphan*/  CMD_OK_FOR_HEADER ; 
 int /*<<< orphan*/  CMD_POP ; 
 int /*<<< orphan*/  CMD_PUSH ; 
 int /*<<< orphan*/  CMD_TABLES_YYDMAP ; 
 int C_plus_plus ; 
 int MAXLINE ; 
 int /*<<< orphan*/  OUT_BEGIN_CODE () ; 
 int /*<<< orphan*/  OUT_END_CODE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bison_bridge_lval ; 
 int /*<<< orphan*/  chomp (char*) ; 
 scalar_t__ cmd_match (int /*<<< orphan*/ ) ; 
 scalar_t__ ddebug ; 
 int /*<<< orphan*/ * fgets (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  flexfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_str (char*,char*) ; 
 int /*<<< orphan*/  outn (char*) ; 
 scalar_t__ reentrant ; 
 scalar_t__* skel ; 
 int /*<<< orphan*/  skel_ind ; 
 scalar_t__ skelfile ; 
 scalar_t__ sko_len ; 
 int /*<<< orphan*/  sko_peek (int*) ; 
 int /*<<< orphan*/  sko_pop (int*) ; 
 int /*<<< orphan*/  sko_push (int) ; 
 int strlen (char*) ; 
 scalar_t__ tablesext ; 
 char* tablesname ; 
 TYPE_1__ yydmap_buf ; 

void skelout ()
{
	char    buf_storage[MAXLINE];
	char   *buf = buf_storage;
	bool   do_copy = true;

    /* "reset" the state by clearing the buffer and pushing a '1' */
    if(sko_len > 0)
        sko_peek(&do_copy);
    sko_len = 0;
    sko_push(do_copy=true);


	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the skel[] array.
	 */
	while (skelfile ?
	       (fgets (buf, MAXLINE, skelfile) != NULL) :
	       ((buf = (char *) skel[skel_ind++]) != 0)) {

		if (skelfile)
			chomp (buf);

		/* copy from skel array */
		if (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			if (ddebug && buf[1] != '#') {
				if (buf[strlen (buf) - 1] == '\\')
					out_str ("/* %s */\\\n", buf);
				else
					out_str ("/* %s */\n", buf);
			}

			/* We've been accused of using cryptic markers in the skel.
			 * So we'll use emacs-style-hyphenated-commands.
             * We might consider a hash if this if-else-if-else
             * chain gets too large.
			 */
#define cmd_match(s) (strncmp(buf,(s),strlen(s))==0)

			if (buf[1] == '%') {
				/* %% is a break point for skelout() */
				return;
			}
            else if (cmd_match (CMD_PUSH)){
                sko_push(do_copy);
                if(ddebug){
                    out_str("/*(state = (%s) */",do_copy?"true":"false");
                }
                out_str("%s\n", buf[strlen (buf) - 1] =='\\' ? "\\" : "");
            }
            else if (cmd_match (CMD_POP)){
                sko_pop(&do_copy);
                if(ddebug){
                    out_str("/*(state = (%s) */",do_copy?"true":"false");
                }
                out_str("%s\n", buf[strlen (buf) - 1] =='\\' ? "\\" : "");
            }
            else if (cmd_match (CMD_IF_REENTRANT)){
                sko_push(do_copy);
                do_copy = reentrant && do_copy;
            }
            else if (cmd_match (CMD_IF_NOT_REENTRANT)){
                sko_push(do_copy);
                do_copy = !reentrant && do_copy;
            }
            else if (cmd_match(CMD_IF_BISON_BRIDGE)){
                sko_push(do_copy);
                do_copy = bison_bridge_lval && do_copy;
            }
            else if (cmd_match(CMD_IF_NOT_BISON_BRIDGE)){
                sko_push(do_copy);
                do_copy = !bison_bridge_lval && do_copy;
            }
            else if (cmd_match (CMD_ENDIF)){
                sko_pop(&do_copy);
            }
			else if (cmd_match (CMD_IF_TABLES_SER)) {
                do_copy = do_copy && tablesext;
			}
			else if (cmd_match (CMD_TABLES_YYDMAP)) {
				if (tablesext && yydmap_buf.elts)
					outn ((char *) (yydmap_buf.elts));
			}
            else if (cmd_match (CMD_DEFINE_YYTABLES)) {
                out_str("#define YYTABLES_NAME \"%s\"\n",
                        tablesname?tablesname:"yytables");
            }
			else if (cmd_match (CMD_IF_CPP_ONLY)) {
				/* only for C++ */
                sko_push(do_copy);
				do_copy = C_plus_plus;
			}
			else if (cmd_match (CMD_IF_C_ONLY)) {
				/* %- only for C */
                sko_push(do_copy);
				do_copy = !C_plus_plus;
			}
			else if (cmd_match (CMD_IF_C_OR_CPP)) {
				/* %* for C and C++ */
                sko_push(do_copy);
				do_copy = true;
			}
			else if (cmd_match (CMD_NOT_FOR_HEADER)) {
				/* %c begin linkage-only (non-header) code. */
				OUT_BEGIN_CODE ();
			}
			else if (cmd_match (CMD_OK_FOR_HEADER)) {
				/* %e end linkage-only code. */
				OUT_END_CODE ();
			}
			else if (buf[1] == '#') {
				/* %# a comment in the skel. ignore. */
			}
			else {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		else if (do_copy) 
            outn (buf);
	}			/* end while */
}