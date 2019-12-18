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
typedef  int /*<<< orphan*/  hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hb_list_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * hb_list_init () ; 
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hb_subtitle_copy (int /*<<< orphan*/ *) ; 

hb_list_t *hb_subtitle_list_copy(const hb_list_t *src)
{
    hb_list_t *list = hb_list_init();
    hb_subtitle_t *subtitle = NULL;
    int i;

    if( src )
    {
        for( i = 0; i < hb_list_count(src); i++ )
        {
            if( ( subtitle = hb_list_item( src, i ) ) )
            {
                hb_list_add( list, hb_subtitle_copy(subtitle) );
            }
        }
    }
    return list;
}