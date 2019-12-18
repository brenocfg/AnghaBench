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
typedef  int /*<<< orphan*/  hb_value_array_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
typedef  int /*<<< orphan*/  hb_csv_file_t ;
struct TYPE_4__ {int cell_col; int cell_row; int /*<<< orphan*/  cell_text; } ;
typedef  TYPE_1__ hb_csv_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hb_close_csv_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_dispose_cell (TYPE_1__*) ; 
 int /*<<< orphan*/ * hb_open_csv_file (char const*) ; 
 TYPE_1__* hb_read_next_cell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void write_chapter_names(hb_dict_t *job_dict, const char *marker_file)
{
    if (marker_file == NULL)
        return;

    hb_csv_file_t * file = hb_open_csv_file(marker_file);
    hb_csv_cell_t * cell;
    int row = 0;

    if (file == NULL)
    {
        fprintf(stderr, "Cannot open chapter marker file, using defaults\n");
        return;
    }
    fprintf(stderr, "Reading chapter markers from file %s\n", marker_file);

    hb_value_array_t *chapter_array;
    chapter_array = hb_dict_get(hb_dict_get(job_dict, "Destination"),
                                "ChapterList");

    if (chapter_array == NULL)
        return;

    /* Parse the cells */
    while (NULL != (cell = hb_read_next_cell(file)))
    {
        /* We have a chapter number */
        if (cell->cell_col == 0)
        {
            row = cell->cell_row;
        }

        /* We have a chapter name */
        if (cell->cell_col == 1 && row == cell->cell_row)
        {
            /* If we have a valid chapter, add chapter entry */
            hb_dict_t *chapter_dict = hb_value_array_get(chapter_array, row);
            if (chapter_dict != NULL)
            {
                hb_dict_set(chapter_dict, "Name",
                            hb_value_string(cell->cell_text));
            }
        }
        hb_dispose_cell( cell );
    }
    hb_close_csv_file( file );
}