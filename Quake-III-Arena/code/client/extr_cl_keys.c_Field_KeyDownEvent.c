#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cursor; int scroll; int widthInChars; scalar_t__ buffer; } ;
typedef  TYPE_1__ field_t ;
struct TYPE_6__ {scalar_t__ down; } ;

/* Variables and functions */
 int /*<<< orphan*/  Field_Paste (TYPE_1__*) ; 
 size_t K_CTRL ; 
 int K_DEL ; 
 int K_END ; 
 int K_HOME ; 
 int K_INS ; 
 int K_KP_INS ; 
 int K_LEFTARROW ; 
 int K_RIGHTARROW ; 
 size_t K_SHIFT ; 
 int key_overstrikeMode ; 
 TYPE_2__* keys ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int strlen (scalar_t__) ; 
 char tolower (int) ; 

void Field_KeyDownEvent( field_t *edit, int key ) {
	int		len;

	// shift-insert is paste
	if ( ( ( key == K_INS ) || ( key == K_KP_INS ) ) && keys[K_SHIFT].down ) {
		Field_Paste( edit );
		return;
	}

	len = strlen( edit->buffer );

	if ( key == K_DEL ) {
		if ( edit->cursor < len ) {
			memmove( edit->buffer + edit->cursor, 
				edit->buffer + edit->cursor + 1, len - edit->cursor );
		}
		return;
	}

	if ( key == K_RIGHTARROW ) 
	{
		if ( edit->cursor < len ) {
			edit->cursor++;
		}

		if ( edit->cursor >= edit->scroll + edit->widthInChars && edit->cursor <= len )
		{
			edit->scroll++;
		}
		return;
	}

	if ( key == K_LEFTARROW ) 
	{
		if ( edit->cursor > 0 ) {
			edit->cursor--;
		}
		if ( edit->cursor < edit->scroll )
		{
			edit->scroll--;
		}
		return;
	}

	if ( key == K_HOME || ( tolower(key) == 'a' && keys[K_CTRL].down ) ) {
		edit->cursor = 0;
		return;
	}

	if ( key == K_END || ( tolower(key) == 'e' && keys[K_CTRL].down ) ) {
		edit->cursor = len;
		return;
	}

	if ( key == K_INS ) {
		key_overstrikeMode = !key_overstrikeMode;
		return;
	}
}