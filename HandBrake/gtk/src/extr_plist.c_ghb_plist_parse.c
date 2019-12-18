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
struct TYPE_5__ {int /*<<< orphan*/ * plist; void* tag_stack; void* stack; int /*<<< orphan*/ * value; int /*<<< orphan*/ * key; int /*<<< orphan*/  closed_top; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  int /*<<< orphan*/  gssize ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_6__ {int /*<<< orphan*/  error; int /*<<< orphan*/  passthrough; int /*<<< orphan*/  text; int /*<<< orphan*/  end_element; int /*<<< orphan*/  start_element; } ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  TYPE_2__ GMarkupParser ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  destroy_notify ; 
 int /*<<< orphan*/  end_element ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_markup_parse_context_end_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_markup_parse_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_markup_parse_context_new (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_markup_parse_context_parse (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_queue_free (void*) ; 
 void* g_queue_new () ; 
 int /*<<< orphan*/  parse_error ; 
 int /*<<< orphan*/  passthrough ; 
 int /*<<< orphan*/  start_element ; 
 int /*<<< orphan*/  text_data ; 

GhbValue*
ghb_plist_parse(const gchar *buf, gssize len)
{
    GMarkupParseContext *ctx;
    GMarkupParser parser;
    parse_data_t pd;
    GError *err = NULL;

    pd.stack = g_queue_new();
    pd.tag_stack = g_queue_new();
    pd.key = NULL;
    pd.value = NULL;
    pd.plist = NULL;
    pd.closed_top = FALSE;

    parser.start_element = start_element;
    parser.end_element = end_element;
    parser.text = text_data;
    parser.passthrough = passthrough;
    parser.error = parse_error;
    ctx = g_markup_parse_context_new(&parser, 0, &pd, destroy_notify);

    g_markup_parse_context_parse(ctx, buf, len, &err);
    g_markup_parse_context_end_parse(ctx, &err);
    g_markup_parse_context_free(ctx);
    if (pd.key) g_free(pd.key);
    if (pd.value) g_free(pd.value);
    g_queue_free(pd.stack);
    g_queue_free(pd.tag_stack);
    return pd.plist;
}