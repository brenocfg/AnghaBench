#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  password ;
struct TYPE_4__ {char* buffer; int cursor; } ;
struct TYPE_5__ {TYPE_1__ field; } ;
typedef  TYPE_2__ menufield_s ;

/* Variables and functions */
 int MAX_EDIT_LINE ; 
 scalar_t__ Q_isalpha (char) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  Rankings_DrawText (TYPE_2__*) ; 
 int strlen (char*) ; 

void Rankings_DrawPassword( void* self )
{
	menufield_s*	f;
	char			password[MAX_EDIT_LINE];
	int				length;
	int				i;
	char*			p;

	f = (menufield_s*)self;
	
	// GRANK_FIXME - enforce valid characters
	for( p = f->field.buffer; *p != '\0'; p++ )
	{
		//if( ispunct(*p) || isspace(*p) )
		if( !( ( (*p) >= '0' && (*p) <= '9') || Q_isalpha(*p)) )
		{
			*p = '\0';
		}
	}
	
	length = strlen( f->field.buffer );
	if( f->field.cursor > length )
	{
		f->field.cursor = length;
	}
	
	// save password
	Q_strncpyz( password, f->field.buffer, sizeof(password) );

	// mask password with *
	for( i = 0; i < length; i++ )
	{
		f->field.buffer[i] = '*';
	}

	// draw masked password
	Rankings_DrawText( f );
	//MenuField_Draw( f );

	// restore password
	Q_strncpyz( f->field.buffer, password, sizeof(f->field.buffer) );
}