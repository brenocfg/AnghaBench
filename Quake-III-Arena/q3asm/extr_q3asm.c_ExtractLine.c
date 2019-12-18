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
 int /*<<< orphan*/  CodeError (char*) ; 
 int MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  currentFileLine ; 
 scalar_t__* lineBuffer ; 
 scalar_t__ lineParseOffset ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 scalar_t__* token ; 

char *ExtractLine( char *data ) {
	int			i;

	currentFileLine++;
	lineParseOffset = 0;
	token[0] = 0;

	if ( data[0] == 0 ) {
		lineBuffer[0] = 0;
		return NULL;
	}

	for ( i = 0 ; i < MAX_LINE_LENGTH ; i++ ) {
		if ( data[i] == 0 || data[i] == '\n' ) {
			break;
		}
	}
	if ( i == MAX_LINE_LENGTH ) {
		CodeError( "MAX_LINE_LENGTH" );
		return data;
	}
	memcpy( lineBuffer, data, i );
	lineBuffer[i] = 0;
	data += i;
	if ( data[0] == '\n' ) {
		data++;
	}
	return data;
}