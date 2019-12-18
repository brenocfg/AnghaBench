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
struct TYPE_2__ {int ival; } ;

/* Variables and functions */
 int DIGIT ; 
 int LETTER ; 
 int* base ; 
 int getchar () ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ islower (int) ; 
 TYPE_1__* yylval ; 

int
YYLEX_DECL()
{
	/* lexical analysis routine */
	/* returns LETTER for a lower case letter, yylval = 0 through 25 */
	/* return DIGIT for a digit, yylval = 0 through 9 */
	/* all other characters are returned immediately */

    int c;

    while( (c=getchar()) == ' ' )   { /* skip blanks */ }

    /* c is now nonblank */

    if( islower( c )) {
	yylval->ival = (c - 'a');
	return ( LETTER );
    }
    if( isdigit( c )) {
	yylval->ival = (c - '0') % (*base);
	return ( DIGIT );
    }
    return( c );
}