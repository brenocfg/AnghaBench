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
typedef  enum XML_Status { ____Placeholder_XML_Status } XML_Status ;
typedef  int /*<<< orphan*/  XML_Parser ;

/* Variables and functions */
 int XML_Parse (int /*<<< orphan*/ ,char const*,int,int const) ; 
 int XML_STATUS_ERROR ; 
 int XML_STATUS_OK ; 

__attribute__((used)) static enum XML_Status
_XML_Parse_SINGLE_BYTES(XML_Parser parser, const char *s, int len, int isFinal)
{
    enum XML_Status res = XML_STATUS_ERROR;
    int offset = 0;

    if (len == 0) {
        return XML_Parse(parser, s, len, isFinal);
    }

    for (; offset < len; offset++) {
        const int innerIsFinal = (offset == len - 1) && isFinal;
        const char c = s[offset]; /* to help out-of-bounds detection */
        res = XML_Parse(parser, &c, sizeof(char), innerIsFinal);
        if (res != XML_STATUS_OK) {
            return res;
        }
    }
    return res;
}