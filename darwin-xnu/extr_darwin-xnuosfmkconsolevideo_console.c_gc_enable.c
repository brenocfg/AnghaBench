#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable ) (void*) ;int /*<<< orphan*/  (* show_cursor ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* clear_screen ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_3__ {int v_columns; int v_rows; } ;

/* Variables and functions */
 char ATTR_NONE ; 
 char COLOR_CODE_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  COLOR_FOREGROUND ; 
 scalar_t__ FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  VCPUTC_LOCK_LOCK () ; 
 int /*<<< orphan*/  VCPUTC_LOCK_UNLOCK () ; 
 scalar_t__ console_is_serial () ; 
 void* disableConsoleOutput ; 
 unsigned char* gc_buffer_attributes ; 
 unsigned char* gc_buffer_characters ; 
 unsigned char* gc_buffer_colorcodes ; 
 int gc_buffer_columns ; 
 int gc_buffer_rows ; 
 int gc_buffer_size ; 
 unsigned char* gc_buffer_tab_stops ; 
 void* gc_enabled ; 
 TYPE_2__ gc_ops ; 
 int /*<<< orphan*/  gc_reset_screen () ; 
 int /*<<< orphan*/  gc_x ; 
 int /*<<< orphan*/  gc_y ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kfree (unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (void*) ; 
 TYPE_1__ vinfo ; 
 scalar_t__ vm_initialized ; 

__attribute__((used)) static void
gc_enable( boolean_t enable )
{
	unsigned char *buffer_attributes = NULL;
	unsigned char *buffer_characters = NULL;
	unsigned char *buffer_colorcodes = NULL;
	unsigned char *buffer_tab_stops  = NULL;
	uint32_t buffer_columns = 0;
	uint32_t buffer_rows = 0;
	uint32_t buffer_size = 0;
	spl_t s;

	if ( enable == FALSE )
	{
		// only disable console output if it goes to the graphics console
		if ( console_is_serial() == FALSE )
			disableConsoleOutput = TRUE;
		gc_enabled           = FALSE;
		gc_ops.enable(FALSE);
	}

	s = splhigh( );
	VCPUTC_LOCK_LOCK( );

	if ( gc_buffer_size )
	{
		buffer_attributes = gc_buffer_attributes;
		buffer_characters = gc_buffer_characters;
		buffer_colorcodes = gc_buffer_colorcodes;
		buffer_tab_stops  = gc_buffer_tab_stops;
		buffer_columns    = gc_buffer_columns;
		buffer_rows       = gc_buffer_rows;
		buffer_size       = gc_buffer_size;

		gc_buffer_attributes = NULL;
		gc_buffer_characters = NULL;
		gc_buffer_colorcodes = NULL;
		gc_buffer_tab_stops  = NULL;
		gc_buffer_columns    = 0;
		gc_buffer_rows       = 0;
		gc_buffer_size       = 0;

		VCPUTC_LOCK_UNLOCK( );
		splx( s );

		kfree( buffer_attributes, buffer_size );
		kfree( buffer_characters, buffer_size );
		kfree( buffer_colorcodes, buffer_size );
		kfree( buffer_tab_stops,  buffer_columns );
	}
	else
	{
		VCPUTC_LOCK_UNLOCK( );
		splx( s );
	}

	if ( enable )
	{
		if ( vm_initialized )
		{
			buffer_columns = vinfo.v_columns;
			buffer_rows    = vinfo.v_rows;
			buffer_size    = buffer_columns * buffer_rows;

			if ( buffer_size )
			{
				buffer_attributes = (unsigned char *) kalloc( buffer_size );
				buffer_characters = (unsigned char *) kalloc( buffer_size );
				buffer_colorcodes = (unsigned char *) kalloc( buffer_size );
				buffer_tab_stops  = (unsigned char *) kalloc( buffer_columns );

				if ( buffer_attributes == NULL ||
				     buffer_characters == NULL ||
				     buffer_colorcodes == NULL ||
				     buffer_tab_stops  == NULL )
				{
					if ( buffer_attributes ) kfree( buffer_attributes, buffer_size );
					if ( buffer_characters ) kfree( buffer_characters, buffer_size );
					if ( buffer_colorcodes ) kfree( buffer_colorcodes, buffer_size );
					if ( buffer_tab_stops  ) kfree( buffer_tab_stops,  buffer_columns );

					buffer_attributes = NULL;
					buffer_characters = NULL;
					buffer_colorcodes = NULL;
					buffer_tab_stops  = NULL;
					buffer_columns = 0;
					buffer_rows    = 0;
					buffer_size    = 0;
				}
				else
				{
					memset( buffer_attributes, ATTR_NONE, buffer_size );
					memset( buffer_characters, ' ', buffer_size );
					memset( buffer_colorcodes, COLOR_CODE_SET( 0, COLOR_FOREGROUND, TRUE ), buffer_size );
					memset( buffer_tab_stops, 0, buffer_columns );
				}
			}
		}

		s = splhigh( );
		VCPUTC_LOCK_LOCK( );

		gc_buffer_attributes = buffer_attributes;
		gc_buffer_characters = buffer_characters;
		gc_buffer_colorcodes = buffer_colorcodes;
		gc_buffer_tab_stops  = buffer_tab_stops;
		gc_buffer_columns    = buffer_columns;
		gc_buffer_rows       = buffer_rows;
		gc_buffer_size       = buffer_size;

		gc_reset_screen();

		VCPUTC_LOCK_UNLOCK( );
		splx( s );

		gc_ops.clear_screen(gc_x, gc_y, 0, vinfo.v_rows, 2);
		gc_ops.show_cursor(gc_x, gc_y);

		gc_ops.enable(TRUE);
		gc_enabled           = TRUE;
		disableConsoleOutput = FALSE;
	}
}