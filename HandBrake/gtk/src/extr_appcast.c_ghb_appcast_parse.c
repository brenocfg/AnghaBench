#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* version; scalar_t__* build; int /*<<< orphan*/  description; int /*<<< orphan*/  tag_stack; int /*<<< orphan*/ * value; int /*<<< orphan*/ * key; int /*<<< orphan*/  item; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  scalar_t__ gchar ;
struct TYPE_6__ {int /*<<< orphan*/  error; int /*<<< orphan*/  passthrough; int /*<<< orphan*/  text; int /*<<< orphan*/  end_element; int /*<<< orphan*/  start_element; } ;
typedef  TYPE_2__ GMarkupParser ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_MARKUP_TREAT_CDATA_AS_TEXT ; 
 int /*<<< orphan*/  destroy_notify ; 
 int /*<<< orphan*/  end_element ; 
 int /*<<< orphan*/  g_markup_parse_context_end_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_markup_parse_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_markup_parse_context_new (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_markup_parse_context_parse (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_queue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_queue_new () ; 
 scalar_t__* g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_new (char*) ; 
 scalar_t__* g_strrstr (scalar_t__*,char*) ; 
 int /*<<< orphan*/  parse_error ; 
 int /*<<< orphan*/  passthrough ; 
 int /*<<< orphan*/  start_element ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 scalar_t__* strstr (scalar_t__*,char*) ; 
 int /*<<< orphan*/  text_data ; 

void
ghb_appcast_parse(gchar *buf, gchar **desc, gchar **build, gchar **version)
{
    GMarkupParseContext *ctx;
    GMarkupParser parser;
    parse_data_t pd;
    GError *err = NULL;
    gint len;
    gchar *start;
    //gchar tmp[4096]

    // Skip junk at beginning of buffer
    start = strstr(buf, "<?xml ");
    pd.description = g_string_new("");
    pd.item = FALSE;
    pd.build = NULL;
    pd.version = NULL;
    len = strlen(start);
    pd.tag_stack = g_queue_new();
    pd.key = NULL;
    pd.value = NULL;

    parser.start_element = start_element;
    parser.end_element = end_element;
    parser.text = text_data;
    parser.passthrough = passthrough;
    parser.error = parse_error;
    ctx = g_markup_parse_context_new(
            &parser, G_MARKUP_TREAT_CDATA_AS_TEXT, &pd, destroy_notify);

    g_markup_parse_context_parse(ctx, start, len, &err);
    g_markup_parse_context_end_parse(ctx, &err);
    g_markup_parse_context_free(ctx);
    g_queue_free(pd.tag_stack);
    *desc = g_string_free(pd.description, FALSE);
    // work around a bug to leaves the CDATA closing brakets on the string
    gchar *glitch;
    glitch = g_strrstr(*desc, "]]>");
    if (glitch)
        *glitch = 0;
    *build = pd.build;
    *version = pd.version;
}