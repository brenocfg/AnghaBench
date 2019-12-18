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
typedef  int /*<<< orphan*/  XML_Char ;
typedef  int /*<<< orphan*/  CharData ;

/* Variables and functions */
 int /*<<< orphan*/  CharData_CheckXMLChars (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CharData_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ XML_STATUS_ERROR ; 
 int /*<<< orphan*/  XML_SetElementHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ _XML_Parse_SINGLE_BYTES (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  overwrite_end_checker ; 
 int /*<<< orphan*/  overwrite_start_checker ; 
 int /*<<< orphan*/  parser ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xml_failure (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_ns_tagname_overwrite_test(const char *text, const XML_Char *result)
{
    CharData storage;
    CharData_Init(&storage);
    XML_SetUserData(parser, &storage);
    XML_SetElementHandler(parser,
                          overwrite_start_checker, overwrite_end_checker);
    if (_XML_Parse_SINGLE_BYTES(parser, text, (int)strlen(text), XML_TRUE) == XML_STATUS_ERROR)
        xml_failure(parser);
    CharData_CheckXMLChars(&storage, result);
}