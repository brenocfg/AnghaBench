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
typedef  int input_state_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char EOF ; 
#define  IS_IN_COMMENT 132 
#define  IS_IN_END_COMMENT 131 
#define  IS_NORMAL 130 
#define  IS_SLASH 129 
#define  IS_STAR 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char getc_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  putchar_unlocked (char) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char **argv)
{
	FILE *fp;
	char bufchar;
	input_state_t input_state = IS_NORMAL;
	int exit_code = 0;
	int remove_whitespace = 0;
	int arg;
	
	if(argc < 2)
		usage(argv);
	for(arg=2; arg<argc; arg++) {
		switch(argv[arg][0]) {
		    case 'r':
		    	remove_whitespace++;
			break;
		    default:
		    	usage(argv);
		}
	}	
	
	fp = fopen(argv[1], "r");
	if(!fp) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		perror("fopen");
		exit(1);
	}
	for(;;) {
		bufchar = getc_unlocked(fp);
		if (bufchar == EOF)
			break;

		switch(input_state) {
		
		    case IS_NORMAL:
		    	if(bufchar == '/') {
			   	/*
				 * Might be start of a comment.
				 */
				input_state = IS_SLASH;
			}
			else {
				if(!(remove_whitespace && isspace(bufchar))) {
					putchar_unlocked(bufchar);
				}
			}
			break;
			
		    case IS_SLASH:
		    	switch(bufchar) {
			    case '*':
			    	/*
				 * Start of normal comment.
				 */
				input_state = IS_IN_COMMENT;
				break;
				
			    case '/':
			    	/*
				 * Start of 'to-end-of-line' comment.
				 */
				input_state = IS_IN_END_COMMENT;
				break;
				
			    default:
			    	/*
				 * Not the start of comment. Emit the '/'
				 * we skipped last char in case we were
				 * entering a comment this time, then the
				 * current char.
				 */
				putchar_unlocked('/');
				if(!(remove_whitespace && isspace(bufchar))) {
					putchar_unlocked(bufchar);
				}
				input_state = IS_NORMAL;
				break;
			}
			break;
			
		    case IS_IN_COMMENT:
		    	if(bufchar == '*') {
			    	/*
				 * Maybe ending comment...
				 */
			    	input_state = IS_STAR;
			}
		    	break;
	
	
		    case IS_STAR:
		    	switch(bufchar) {
			    case '/':
				/*
				 * End of normal comment.
				 */
				input_state = IS_NORMAL;
				break;
				
			    case '*':
			    	/*
				 * Still could be one char away from end
				 * of comment.
				 */
				break;
				
			    default:
			    	/*
				 * Still inside comment, no end in sight.
				 */
				input_state = IS_IN_COMMENT;
				break;
			}
			break;
			
		    case IS_IN_END_COMMENT:
		    	if(bufchar == '\n') {
				/*
				 * End of comment. Emit the newline if 
				 * appropriate.
				 */
				if(!remove_whitespace) {
					putchar_unlocked(bufchar);
				}
				input_state = IS_NORMAL;
			}
			break;
		
		} /* switch input_state */
	} 	  /* main read loop */
	
	/*
	 * Done.
	 */
	return(exit_code);
}