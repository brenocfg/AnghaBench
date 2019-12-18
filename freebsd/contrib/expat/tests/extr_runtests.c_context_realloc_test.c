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
struct TYPE_3__ {char* member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ExtOption ;

/* Variables and functions */
 int /*<<< orphan*/ * XCS (char*) ; 
 int /*<<< orphan*/  XML_PARAM_ENTITY_PARSING_ALWAYS ; 
 scalar_t__ XML_STATUS_ERROR ; 
 int /*<<< orphan*/  XML_SetExternalEntityRefHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetParamEntityParsing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ _XML_Parse_SINGLE_BYTES (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  external_entity_optioner ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  nsalloc_setup () ; 
 int /*<<< orphan*/  nsalloc_teardown () ; 
 int /*<<< orphan*/  parser ; 
 int reallocation_count ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
context_realloc_test(const char *text)
{
    ExtOption options[] = {
        { XCS("foo"), "<!ELEMENT e EMPTY>"},
        { XCS("bar"), "<e/>" },
        { NULL, NULL }
    };
    int i;
    const int max_realloc_count = 6;

    for (i = 0; i < max_realloc_count; i++) {
        reallocation_count = i;
        XML_SetUserData(parser, options);
        XML_SetParamEntityParsing(parser, XML_PARAM_ENTITY_PARSING_ALWAYS);
        XML_SetExternalEntityRefHandler(parser, external_entity_optioner);
        if (_XML_Parse_SINGLE_BYTES(parser, text, (int)strlen(text),
                                    XML_TRUE) != XML_STATUS_ERROR)
            break;
        /* See comment in test_nsalloc_xmlns() */
        nsalloc_teardown();
        nsalloc_setup();
    }
    if (i == 0)
        fail("Parsing worked despite failing reallocations");
    else if (i == max_realloc_count)
        fail("Parsing failed even at max reallocation count");
}