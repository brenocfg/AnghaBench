#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* cur_elem; } ;
typedef  TYPE_1__ apr_xml_parser ;
struct TYPE_6__ {int ns; scalar_t__ emptyURI; int /*<<< orphan*/  prefix; struct TYPE_6__* next; } ;
typedef  TYPE_2__ apr_xml_ns_scope ;
struct TYPE_7__ {TYPE_2__* ns_scope; struct TYPE_7__* parent; } ;
typedef  TYPE_3__ apr_xml_elem ;

/* Variables and functions */
 int APR_XML_NS_ERROR_UNKNOWN_PREFIX ; 
 int APR_XML_NS_NONE ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_prefix(apr_xml_parser *parser, const char *prefix)
{
    apr_xml_elem *elem = parser->cur_elem;

    /*
    ** Walk up the tree, looking for a namespace scope that defines this
    ** prefix.
    */
    for (; elem; elem = elem->parent) {
	apr_xml_ns_scope *ns_scope = elem->ns_scope;

	for (ns_scope = elem->ns_scope; ns_scope; ns_scope = ns_scope->next) {
	    if (strcmp(prefix, ns_scope->prefix) == 0) {
		if (ns_scope->emptyURI) {
		    /*
		    ** It is possible to set the default namespace to an
		    ** empty URI string; this resets the default namespace
		    ** to mean "no namespace." We just found the prefix
		    ** refers to an empty URI, so return "no namespace."
		    */
		    return APR_XML_NS_NONE;
		}

		return ns_scope->ns;
	    }
	}
    }

    /*
     * If the prefix is empty (""), this means that a prefix was not
     * specified in the element/attribute. The search that was performed
     * just above did not locate a default namespace URI (which is stored
     * into ns_scope with an empty prefix). This means the element/attribute
     * has "no namespace". We have a reserved value for this.
     */
    if (*prefix == '\0') {
	return APR_XML_NS_NONE;
    }

    /* not found */
    return APR_XML_NS_ERROR_UNKNOWN_PREFIX;
}