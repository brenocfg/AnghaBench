#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int hash; int value; struct TYPE_5__* next; int /*<<< orphan*/  segment; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ symbol_t ;

/* Variables and functions */
 int /*<<< orphan*/  CodeError (char*,char*) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 int HashString (char*) ; 
 int MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  copystring (char*) ; 
 int currentFileIndex ; 
 int /*<<< orphan*/  currentSegment ; 
 TYPE_1__* lastSymbol ; 
 TYPE_1__* malloc (int) ; 
 int passNumber ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* symbols ; 

void DefineSymbol( char *sym, int value ) {
	symbol_t	*s, *after;
	char		expanded[MAX_LINE_LENGTH];
	int			hash;

	if ( passNumber == 1 ) {
		return;
	}
  
  // TTimo
  // https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=381
  // as a security, bail out if vmMain entry point is not first
  if (!Q_stricmp(sym, "vmMain"))
    if (value)
      Error( "vmMain must be the first symbol in the qvm (got offset %d)\n", value );

	// add the file prefix to local symbols to guarantee unique
	if ( sym[0] == '$' ) {
		sprintf( expanded, "%s_%i", sym, currentFileIndex );
		sym = expanded;
	}

	hash = HashString( sym );

	for ( s = symbols ; s ; s = s->next ) {
		if ( hash == s->hash && !strcmp( sym, s->name ) ) {
			CodeError( "Multiple definitions for %s\n", sym );
			return;
		}
	}

	s = malloc( sizeof( *s ) );
	s->name = copystring( sym );
	s->hash = hash;
	s->value = value;
	s->segment = currentSegment;

	lastSymbol = s;	/* for the move-to-lit-segment byteswap hack */

	// insert it in order
	if ( !symbols || s->value < symbols->value ) {
		s->next = symbols;
		symbols = s;
		return;
	}

	for ( after = symbols ; after->next && after->next->value < value ; after = after->next ) {
	}
	s->next = after->next;
	after->next = s;
}