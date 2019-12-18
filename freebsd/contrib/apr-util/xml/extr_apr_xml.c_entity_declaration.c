#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  xp; } ;
typedef  TYPE_1__ apr_xml_parser ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  XML_FALSE ; 
 int /*<<< orphan*/  XML_StopParser (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void entity_declaration(void *userData, const XML_Char *entityName,
                               int is_parameter_entity, const XML_Char *value,
                               int value_length, const XML_Char *base,
                               const XML_Char *systemId, const XML_Char *publicId,
                               const XML_Char *notationName)
{
    apr_xml_parser *parser = userData;

    XML_StopParser(parser->xp, XML_FALSE);
}