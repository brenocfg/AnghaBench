#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_error_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
struct TYPE_3__ {int /*<<< orphan*/  list_title; int /*<<< orphan*/  feature; } ;
typedef  TYPE_1__ hb_title_set_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * hb_title_to_dict_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_pack_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 

hb_dict_t* hb_title_set_to_dict( const hb_title_set_t * title_set )
{
    hb_dict_t *dict;
    json_error_t error;
    int ii;

    dict = json_pack_ex(&error, 0,
        "{s:o, s:[]}",
        "MainFeature", hb_value_int(title_set->feature),
        "TitleList");
    // process title list
    hb_dict_t *title_list = hb_dict_get(dict, "TitleList");
    for (ii = 0; ii < hb_list_count(title_set->list_title); ii++)
    {
        hb_title_t *title = hb_list_item(title_set->list_title, ii);
        hb_dict_t *title_dict = hb_title_to_dict_internal(title);
        hb_value_array_append(title_list, title_dict);
    }

    return dict;
}