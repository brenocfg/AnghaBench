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
typedef  int /*<<< orphan*/  hb_title_t ;
struct TYPE_4__ {int /*<<< orphan*/  feature; int /*<<< orphan*/  list_title; } ;
typedef  TYPE_1__ hb_title_set_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  PrintTitleInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * hb_title_set_to_dict (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 scalar_t__ json ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void PrintTitleSetInfo( hb_title_set_t * title_set )
{
    if (json)
    {
        hb_dict_t * title_set_dict;
        char      * title_set_json;

        title_set_dict = hb_title_set_to_dict(title_set);
        title_set_json = hb_value_get_json(title_set_dict);
        hb_value_free(&title_set_dict);
        fprintf(stdout, "JSON Title Set: %s\n", title_set_json);
        free(title_set_json);
    }
    else
    {
        int i;
        hb_title_t * title;

        for( i = 0; i < hb_list_count( title_set->list_title ); i++ )
        {
            title = hb_list_item( title_set->list_title, i );
            PrintTitleInfo( title, title_set->feature );
        }
    }
}