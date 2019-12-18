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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 char* lineBuffer ; 
 size_t lineParseOffset ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int* token ; 

qboolean Parse( void ) {
	int		c;
	int		len;
	
	len = 0;
	token[0] = 0;
	
	// skip whitespace
	while ( lineBuffer[ lineParseOffset ] <= ' ' ) {
		if ( lineBuffer[ lineParseOffset ] == 0 ) {
			return qfalse;
		}
		lineParseOffset++;
	}

	// skip ; comments
	c = lineBuffer[ lineParseOffset ];
	if ( c == ';' ) {
		return qfalse;
	}
	

	// parse a regular word
	do {
		token[len] = c;
		len++;
		lineParseOffset++;
		c = lineBuffer[ lineParseOffset ];
	} while (c>32);
	
	token[len] = 0;
	return qtrue;
}