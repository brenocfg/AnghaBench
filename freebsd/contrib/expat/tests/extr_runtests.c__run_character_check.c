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
 int /*<<< orphan*/  XML_SetCharacterDataHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ _XML_Parse_SINGLE_BYTES (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _xml_failure (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  accumulate_characters ; 
 int /*<<< orphan*/  parser ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
_run_character_check(const char *text, const XML_Char *expected,
                     const char *file, int line)
{
    CharData storage;

    CharData_Init(&storage);
    XML_SetUserData(parser, &storage);
    XML_SetCharacterDataHandler(parser, accumulate_characters);
    if (_XML_Parse_SINGLE_BYTES(parser, text, (int)strlen(text), XML_TRUE) == XML_STATUS_ERROR)
        _xml_failure(parser, file, line);
    CharData_CheckXMLChars(&storage, expected);
}