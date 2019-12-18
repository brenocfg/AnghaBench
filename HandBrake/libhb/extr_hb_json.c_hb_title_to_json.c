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
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_title_to_dict (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 

char* hb_title_to_json( hb_handle_t *h, int title_index )
{
    hb_dict_t *dict = hb_title_to_dict(h, title_index);
    if (dict == NULL)
        return NULL;

    char *json_title = hb_value_get_json(dict);
    hb_value_free(&dict);

    return json_title;
}