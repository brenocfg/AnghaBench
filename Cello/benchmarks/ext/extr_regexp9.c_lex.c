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
 int BOL ; 
 int END ; 
 int EOL ; 
 int LBRA ; 
 int OR ; 
 int PLUS ; 
 int QUEST ; 
 int RBRA ; 
 int RUNE ; 
 int STAR ; 
 int bldcclass () ; 
 int nextc (int*) ; 
 int yyrune ; 

__attribute__((used)) static	int
lex(int literal, int dot_type)
{
	int quoted;

	quoted = nextc(&yyrune);
	if(literal || quoted){
		if(yyrune == 0)
			return END;
		return RUNE;
	}

	switch(yyrune){
	case 0:
		return END;
	case '*':
		return STAR;
	case '?':
		return QUEST;
	case '+':
		return PLUS;
	case '|':
		return OR;
	case '.':
		return dot_type;
	case '(':
		return LBRA;
	case ')':
		return RBRA;
	case '^':
		return BOL;
	case '$':
		return EOL;
	case '[':
		return bldcclass();
	}
	return RUNE;
}