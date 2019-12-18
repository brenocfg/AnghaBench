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
struct TYPE_3__ {void* version; void* build; int /*<<< orphan*/  item; int /*<<< orphan*/  tag_stack; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  scalar_t__ gpointer ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {size_t id; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
#define  A_ENCLOSURE 129 
#define  A_ITEM 128 
 size_t A_NONE ; 
 size_t TAG_MAP_SZ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_queue_push_head (int /*<<< orphan*/ ,scalar_t__) ; 
 void* g_strdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * lookup_attr_value (char*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* tag_map ; 

__attribute__((used)) static void
start_element(
    GMarkupParseContext *ctx,
    const gchar *tag,
    const gchar **attr_names,
    const gchar **attr_values,
    gpointer ud,
    GError **error)
{
    parse_data_t *pd = (parse_data_t*)ud;
    union
    {
        gint id;
        gpointer pid;
    } id;
    gint ii;

    for (ii = 0; ii < TAG_MAP_SZ; ii++)
    {
        if (strcmp(tag, tag_map[ii].tag) == 0)
        {
            id.id = tag_map[ii].id;
            break;
        }
    }
    if (ii == TAG_MAP_SZ)
    {
        g_debug("Unrecognized start tag (%s)", tag);
        id.id = A_NONE;
    }
    g_queue_push_head(pd->tag_stack, id.pid);
    switch (id.id)
    {
        case A_ITEM:
        {
            pd->item = TRUE;
        } break;
        case A_ENCLOSURE:
        {
            const gchar *build, *version;
            build = lookup_attr_value(
                        "sparkle:version", attr_names, attr_values);
            version = lookup_attr_value(
                        "sparkle:shortVersionString", attr_names, attr_values);
            if (build)
                pd->build = g_strdup(build);
            if (version)
                pd->version = g_strdup(version);
        } break;
    }
}