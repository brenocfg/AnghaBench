#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ curr_row; scalar_t__ curr_col; int /*<<< orphan*/  parse_state; scalar_t__ eof; int /*<<< orphan*/ * fileref; } ;
typedef  TYPE_1__ hb_csv_file_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CSV_PARSE_SEEK ; 
 int /*<<< orphan*/ * hb_fopen (char const*,char*) ; 
 TYPE_1__* malloc (int) ; 

hb_csv_file_t *hb_open_csv_file( const char *filepath )
{
    hb_csv_file_t *file = NULL;
    FILE * fileref;

    if( filepath == NULL )
    {
        return file;
    }

    fileref = hb_fopen(filepath, "r");
    if( fileref == NULL )
    {
        return file;
    }

    file = malloc( sizeof( hb_csv_file_t ) );
    if( file == NULL )
    {
        return file;
    }

    file->fileref       = fileref;
    file->eof           = 0;
    file->parse_state   = CSV_PARSE_SEEK;
    file->curr_col      = 0;
    file->curr_row      = 0;
    return file;
}