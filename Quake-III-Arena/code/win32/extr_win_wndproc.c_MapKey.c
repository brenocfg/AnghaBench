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
#define  K_DEL 138 
#define  K_DOWNARROW 137 
#define  K_END 136 
#define  K_HOME 135 
#define  K_INS 134 
 int K_KP_DEL ; 
 int K_KP_DOWNARROW ; 
 int K_KP_END ; 
 int K_KP_ENTER ; 
 int K_KP_HOME ; 
 int K_KP_INS ; 
 int K_KP_LEFTARROW ; 
 int K_KP_NUMLOCK ; 
 int K_KP_PGDN ; 
 int K_KP_PGUP ; 
 int K_KP_PLUS ; 
 int K_KP_RIGHTARROW ; 
 int K_KP_SLASH ; 
 int K_KP_UPARROW ; 
#define  K_LEFTARROW 133 
#define  K_PAUSE 132 
#define  K_PGDN 131 
#define  K_PGUP 130 
#define  K_RIGHTARROW 129 
#define  K_UPARROW 128 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int* s_scantokey ; 

__attribute__((used)) static int MapKey (int key)
{
	int result;
	int modified;
	qboolean is_extended;

//	Com_Printf( "0x%x\n", key);

	modified = ( key >> 16 ) & 255;

	if ( modified > 127 )
		return 0;

	if ( key & ( 1 << 24 ) )
	{
		is_extended = qtrue;
	}
	else
	{
		is_extended = qfalse;
	}

	result = s_scantokey[modified];

	if ( !is_extended )
	{
		switch ( result )
		{
		case K_HOME:
			return K_KP_HOME;
		case K_UPARROW:
			return K_KP_UPARROW;
		case K_PGUP:
			return K_KP_PGUP;
		case K_LEFTARROW:
			return K_KP_LEFTARROW;
		case K_RIGHTARROW:
			return K_KP_RIGHTARROW;
		case K_END:
			return K_KP_END;
		case K_DOWNARROW:
			return K_KP_DOWNARROW;
		case K_PGDN:
			return K_KP_PGDN;
		case K_INS:
			return K_KP_INS;
		case K_DEL:
			return K_KP_DEL;
		default:
			return result;
		}
	}
	else
	{
		switch ( result )
		{
		case K_PAUSE:
			return K_KP_NUMLOCK;
		case 0x0D:
			return K_KP_ENTER;
		case 0x2F:
			return K_KP_SLASH;
		case 0xAF:
			return K_KP_PLUS;
		}
		return result;
	}
}