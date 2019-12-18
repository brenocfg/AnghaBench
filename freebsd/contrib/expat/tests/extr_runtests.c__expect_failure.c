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
typedef  enum XML_Error { ____Placeholder_XML_Error } XML_Error ;

/* Variables and functions */
 int XML_GetErrorCode (int /*<<< orphan*/ ) ; 
 scalar_t__ XML_STATUS_OK ; 
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ _XML_Parse_SINGLE_BYTES (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fail_unless (int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  _xml_failure (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  parser ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
_expect_failure(const char *text, enum XML_Error errorCode, const char *errorMessage,
                const char *file, int lineno)
{
    if (_XML_Parse_SINGLE_BYTES(parser, text, (int)strlen(text), XML_TRUE) == XML_STATUS_OK)
        /* Hackish use of _fail_unless() macro, but let's us report
           the right filename and line number. */
        _fail_unless(0, file, lineno, errorMessage);
    if (XML_GetErrorCode(parser) != errorCode)
        _xml_failure(parser, file, lineno);
}