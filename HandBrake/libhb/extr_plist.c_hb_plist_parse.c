#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  error; int /*<<< orphan*/  warning; int /*<<< orphan*/  characters; int /*<<< orphan*/  endElement; int /*<<< orphan*/  startElement; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_1__ xmlSAXHandler ;
typedef  int /*<<< orphan*/  parser ;
struct TYPE_7__ {int /*<<< orphan*/ * plist; void* tag_stack; void* stack; int /*<<< orphan*/ * value; int /*<<< orphan*/ * key; scalar_t__ closed_top; } ;
typedef  TYPE_2__ parse_data_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  XML_SAX2_MAGIC ; 
 int /*<<< orphan*/  end_element ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_error ; 
 int /*<<< orphan*/  parse_warning ; 
 int /*<<< orphan*/  queue_free (void**) ; 
 void* queue_new () ; 
 int /*<<< orphan*/  start_element ; 
 int /*<<< orphan*/  text_data ; 
 int /*<<< orphan*/  xmlCleanupParser () ; 
 int xmlSAXUserParseMemory (TYPE_1__*,TYPE_2__*,char const*,size_t) ; 

hb_value_t*
hb_plist_parse(const char *buf, size_t len)
{
    xmlSAXHandler parser;
    parse_data_t pd;

    pd.stack = queue_new();
    pd.tag_stack = queue_new();
    pd.key = NULL;
    pd.value = NULL;
    pd.plist = NULL;
    pd.closed_top = 0;

    memset(&parser, 0, sizeof(parser));
    parser.initialized = XML_SAX2_MAGIC;
    parser.startElement = start_element;
    parser.endElement = end_element;
    parser.characters = text_data;
    parser.warning = parse_warning;
    parser.error = parse_error;
    int result = xmlSAXUserParseMemory(&parser, &pd, buf, len);
    if (result != 0)
    {
        hb_error("Plist parse failed");
        return NULL;
    }
    xmlCleanupParser();

    if (pd.key) free(pd.key);
    if (pd.value) free(pd.value);
    queue_free(&pd.stack);
    queue_free(&pd.tag_stack);

    return pd.plist;
}