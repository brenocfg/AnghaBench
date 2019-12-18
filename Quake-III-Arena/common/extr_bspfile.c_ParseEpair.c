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
struct TYPE_5__ {void* value; void* key; } ;
typedef  TYPE_1__ epair_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int MAX_KEY ; 
 int MAX_VALUE ; 
 int /*<<< orphan*/  StripTrailing (void*) ; 
 void* copystring (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token ; 

epair_t *ParseEpair( void ) {
	epair_t	*e;

	e = malloc( sizeof(epair_t) );
	memset( e, 0, sizeof(epair_t) );
	
	if ( strlen(token) >= MAX_KEY-1 ) {
		Error ("ParseEpar: token too long");
	}
	e->key = copystring( token );
	GetToken( qfalse );
	if ( strlen(token) >= MAX_VALUE-1 ) {
		Error ("ParseEpar: token too long");
	}
	e->value = copystring( token );

	// strip trailing spaces that sometimes get accidentally
	// added in the editor
	StripTrailing( e->key );
	StripTrailing( e->value );

	return e;
}