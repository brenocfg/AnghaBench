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
struct TYPE_3__ {int /*<<< orphan*/  item; int /*<<< orphan*/  tag_stack; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  scalar_t__ gpointer ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {size_t id; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
#define  A_ITEM 128 
 size_t A_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 size_t TAG_MAP_SZ ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/  const*) ; 
 scalar_t__ g_queue_pop_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/  const*,size_t,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* tag_map ; 

__attribute__((used)) static void
end_element(
    GMarkupParseContext *ctx,
    const gchar *tag,
    gpointer ud,
    GError **error)
{
    parse_data_t *pd = (parse_data_t*)ud;
    gint id;
    union
    {
        gint id;
        gpointer pid;
    } start_id;
    gint ii;

    for (ii = 0; ii < TAG_MAP_SZ; ii++)
    {
        if (strcmp(tag, tag_map[ii].tag) == 0)
        {
            id = tag_map[ii].id;
            break;
        }
    }
    if (ii == TAG_MAP_SZ)
    {
        g_debug("Unrecognized end tag (%s)", tag);
        id = A_NONE;
    }
    start_id.pid = g_queue_pop_head(pd->tag_stack);
    if (start_id.id != id)
        g_warning("start tag != end tag: (%s %d) %d", tag, start_id.id, id);
    switch (id)
    {
        case A_ITEM:
        {
            pd->item = FALSE;
        } break;
        default:
        {
        } break;
    }

}