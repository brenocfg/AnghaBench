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

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ascii_code_str ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bol () ; 
 int /*<<< orphan*/  bottom () ; 
 int /*<<< orphan*/  command_prompt () ; 
 int /*<<< orphan*/  del_char () ; 
 int /*<<< orphan*/  del_line () ; 
 int /*<<< orphan*/  del_word () ; 
 int /*<<< orphan*/  delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down () ; 
 int /*<<< orphan*/  eol () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ horiz_offset ; 
 int in ; 
 int /*<<< orphan*/  insert (int) ; 
 int /*<<< orphan*/  insert_line (int /*<<< orphan*/ ) ; 
 scalar_t__ last_line ; 
 int /*<<< orphan*/  left (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_menu ; 
 int /*<<< orphan*/  max (int,scalar_t__) ; 
 int /*<<< orphan*/  menu_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_rel (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  right (int /*<<< orphan*/ ) ; 
 scalar_t__ scr_horz ; 
 int /*<<< orphan*/  scr_vert ; 
 int /*<<< orphan*/  search (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_prompt () ; 
 int /*<<< orphan*/  text_win ; 
 int /*<<< orphan*/  top () ; 
 int /*<<< orphan*/  undel_char () ; 
 int /*<<< orphan*/  undel_line () ; 
 int /*<<< orphan*/  undel_word () ; 
 int /*<<< orphan*/  up () ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void 
control()			/* use control for commands		*/
{
	char *string;

	if (in == 1)		/* control a	*/
	{
		string = get_string(ascii_code_str, TRUE);
		if (*string != '\0')
		{
			in = atoi(string);
			wmove(text_win, scr_vert, (scr_horz - horiz_offset));
			insert(in);
		}
		free(string);
	}
	else if (in == 2)	/* control b	*/
		bottom();
	else if (in == 3)	/* control c	*/
	{
		command_prompt();
	}
	else if (in == 4)	/* control d	*/
		down();
	else if (in == 5)	/* control e	*/
		search_prompt();
	else if (in == 6)	/* control f	*/
		undel_char();
	else if (in == 7)	/* control g	*/
		bol();
	else if (in == 8)	/* control h	*/
		delete(TRUE);
	else if (in == 9)	/* control i	*/
		;
	else if (in == 10)	/* control j	*/
		insert_line(TRUE);
	else if (in == 11)	/* control k	*/
		del_char();
	else if (in == 12)	/* control l	*/
		left(TRUE);
	else if (in == 13)	/* control m	*/
		insert_line(TRUE);
	else if (in == 14)	/* control n	*/
		move_rel('d', max(5, (last_line - 5)));
	else if (in == 15)	/* control o	*/
		eol();
	else if (in == 16)	/* control p	*/
		move_rel('u', max(5, (last_line - 5)));
	else if (in == 17)	/* control q	*/
		;
	else if (in == 18)	/* control r	*/
		right(TRUE);
	else if (in == 19)	/* control s	*/
		;
	else if (in == 20)	/* control t	*/
		top();
	else if (in == 21)	/* control u	*/
		up();
	else if (in == 22)	/* control v	*/
		undel_word();
	else if (in == 23)	/* control w	*/
		del_word();
	else if (in == 24)	/* control x	*/
		search(TRUE);
	else if (in == 25)	/* control y	*/
		del_line();
	else if (in == 26)	/* control z	*/
		undel_line();
	else if (in == 27)	/* control [ (escape)	*/
	{
		menu_op(main_menu);
	}	
}