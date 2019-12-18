#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* error; int /*<<< orphan*/  p; TYPE_1__* doc; TYPE_4__* cur_elem; } ;
typedef  TYPE_2__ apr_xml_parser ;
struct TYPE_10__ {char const* prefix; int emptyURI; struct TYPE_10__* next; int /*<<< orphan*/  ns; } ;
typedef  TYPE_3__ apr_xml_ns_scope ;
struct TYPE_11__ {char* name; TYPE_5__* attr; void* ns; int /*<<< orphan*/ * lang; struct TYPE_11__* parent; TYPE_3__* ns_scope; struct TYPE_11__* last_child; struct TYPE_11__* next; struct TYPE_11__* first_child; } ;
typedef  TYPE_4__ apr_xml_elem ;
struct TYPE_12__ {char* name; char* value; void* ns; struct TYPE_12__* next; } ;
typedef  TYPE_5__ apr_xml_attr ;
struct TYPE_8__ {int /*<<< orphan*/  namespaces; TYPE_4__* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_KW_xmlns ; 
 int /*<<< orphan*/  APR_KW_xmlns_lang ; 
 void* APR_XML_NS_ERROR_INVALID_DECL ; 
 scalar_t__ APR_XML_NS_IS_ERROR (void*) ; 
 scalar_t__ APR_XML_NS_IS_RESERVED (char*) ; 
 void* APR_XML_NS_NONE ; 
 TYPE_5__* apr_palloc (int /*<<< orphan*/ ,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  apr_xml_insert_uri (int /*<<< orphan*/ ,char const*) ; 
 void* apr_xml_quote_string (int /*<<< orphan*/ ,char*,int) ; 
 void* find_prefix (TYPE_2__*,char*) ; 
 char* strchr (char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void start_handler(void *userdata, const char *name, const char **attrs)
{
    apr_xml_parser *parser = userdata;
    apr_xml_elem *elem;
    apr_xml_attr *attr;
    apr_xml_attr *prev;
    char *colon;
    const char *quoted;
    char *elem_name;

    /* punt once we find an error */
    if (parser->error)
	return;

    elem = apr_pcalloc(parser->p, sizeof(*elem));

    /* prep the element */
    elem->name = elem_name = apr_pstrdup(parser->p, name);

    /* fill in the attributes (note: ends up in reverse order) */
    while (*attrs) {
	attr = apr_palloc(parser->p, sizeof(*attr));
	attr->name = apr_pstrdup(parser->p, *attrs++);
	attr->value = apr_pstrdup(parser->p, *attrs++);
	attr->next = elem->attr;
	elem->attr = attr;
    }

    /* hook the element into the tree */
    if (parser->cur_elem == NULL) {
	/* no current element; this also becomes the root */
	parser->cur_elem = parser->doc->root = elem;
    }
    else {
	/* this element appeared within the current elem */
	elem->parent = parser->cur_elem;

	/* set up the child/sibling links */
	if (elem->parent->last_child == NULL) {
	    /* no first child either */
	    elem->parent->first_child = elem->parent->last_child = elem;
	}
	else {
	    /* hook onto the end of the parent's children */
	    elem->parent->last_child->next = elem;
	    elem->parent->last_child = elem;
	}

	/* this element is now the current element */
	parser->cur_elem = elem;
    }

    /* scan the attributes for namespace declarations */
    for (prev = NULL, attr = elem->attr;
	 attr;
	 attr = attr->next) {
	if (strncmp(attr->name, APR_KW_xmlns, 5) == 0) {
	    const char *prefix = &attr->name[5];
	    apr_xml_ns_scope *ns_scope;

	    /* test for xmlns:foo= form and xmlns= form */
	    if (*prefix == 0x3A) {
                /* a namespace prefix declaration must have a
                   non-empty value. */
                if (attr->value[0] == '\0') {
                    parser->error = APR_XML_NS_ERROR_INVALID_DECL;
                    return;
                }
		++prefix;
            }
	    else if (*prefix != '\0') {
		/* advance "prev" since "attr" is still present */
		prev = attr;
		continue;
	    }

	    /* quote the URI before we ever start working with it */
	    quoted = apr_xml_quote_string(parser->p, attr->value, 1);

	    /* build and insert the new scope */
	    ns_scope = apr_pcalloc(parser->p, sizeof(*ns_scope));
	    ns_scope->prefix = prefix;
	    ns_scope->ns = apr_xml_insert_uri(parser->doc->namespaces, quoted);
	    ns_scope->emptyURI = *quoted == '\0';
	    ns_scope->next = elem->ns_scope;
	    elem->ns_scope = ns_scope;

	    /* remove this attribute from the element */
	    if (prev == NULL)
		elem->attr = attr->next;
	    else
		prev->next = attr->next;

	    /* Note: prev will not be advanced since we just removed "attr" */
	}
	else if (strcmp(attr->name, APR_KW_xmlns_lang) == 0) {
	    /* save away the language (in quoted form) */
	    elem->lang = apr_xml_quote_string(parser->p, attr->value, 1);

	    /* remove this attribute from the element */
	    if (prev == NULL)
		elem->attr = attr->next;
	    else
		prev->next = attr->next;

	    /* Note: prev will not be advanced since we just removed "attr" */
	}
	else {
	    /* advance "prev" since "attr" is still present */
	    prev = attr;
	}
    }

    /*
    ** If an xml:lang attribute didn't exist (lang==NULL), then copy the
    ** language from the parent element (if present).
    **
    ** NOTE: elem_size() *depends* upon this pointer equality.
    */
    if (elem->lang == NULL && elem->parent != NULL)
	elem->lang = elem->parent->lang;

    /* adjust the element's namespace */
    colon = strchr(elem_name, 0x3A);
    if (colon == NULL) {
	/*
	 * The element is using the default namespace, which will always
	 * be found. Either it will be "no namespace", or a default
	 * namespace URI has been specified at some point.
	 */
	elem->ns = find_prefix(parser, "");
    }
    else if (APR_XML_NS_IS_RESERVED(elem->name)) {
	elem->ns = APR_XML_NS_NONE;
    }
    else {
	*colon = '\0';
	elem->ns = find_prefix(parser, elem->name);
	elem->name = colon + 1;

	if (APR_XML_NS_IS_ERROR(elem->ns)) {
	    parser->error = elem->ns;
	    return;
	}
    }

    /* adjust all remaining attributes' namespaces */
    for (attr = elem->attr; attr; attr = attr->next) {
        /*
         * apr_xml_attr defines this as "const" but we dup'd it, so we
         * know that we can change it. a bit hacky, but the existing
         * structure def is best.
         */
        char *attr_name = (char *)attr->name;

	colon = strchr(attr_name, 0x3A);
	if (colon == NULL) {
	    /*
	     * Attributes do NOT use the default namespace. Therefore,
	     * we place them into the "no namespace" category.
	     */
	    attr->ns = APR_XML_NS_NONE;
	}
	else if (APR_XML_NS_IS_RESERVED(attr->name)) {
	    attr->ns = APR_XML_NS_NONE;
	}
	else {
	    *colon = '\0';
	    attr->ns = find_prefix(parser, attr->name);
	    attr->name = colon + 1;

	    if (APR_XML_NS_IS_ERROR(attr->ns)) {
		parser->error = attr->ns;
		return;
	    }
	}
    }
}