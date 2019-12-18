#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlnsNamespace ;
typedef  int /*<<< orphan*/  xmlNamespace ;
typedef  enum XML_Error { ____Placeholder_XML_Error } XML_Error ;
typedef  TYPE_2__* XML_Parser ;
typedef  char XML_Char ;
typedef  int XML_Bool ;
struct TYPE_15__ {int uriAlloc; char* uri; int uriLen; struct TYPE_15__* nextTagBinding; struct TYPE_15__* prevPrefixBinding; int /*<<< orphan*/  const* attId; TYPE_3__* prefix; } ;
struct TYPE_14__ {scalar_t__* name; TYPE_4__* binding; } ;
struct TYPE_13__ {char m_namespaceSeparator; int /*<<< orphan*/  m_handlerArg; int /*<<< orphan*/  (* m_startNamespaceDeclHandler ) (int /*<<< orphan*/ ,scalar_t__*,char const*) ;TYPE_1__* m_dtd; TYPE_4__* m_freeBindingList; } ;
struct TYPE_12__ {TYPE_3__ defaultPrefix; } ;
typedef  TYPE_3__ PREFIX ;
typedef  TYPE_4__ BINDING ;
typedef  int /*<<< orphan*/  ATTRIBUTE_ID ;

/* Variables and functions */
#define  ASCII_0 154 
#define  ASCII_1 153 
#define  ASCII_2 152 
#define  ASCII_3 151 
#define  ASCII_8 150 
#define  ASCII_9 149 
#define  ASCII_COLON 148 
#define  ASCII_L 147 
#define  ASCII_M 146 
#define  ASCII_PERIOD 145 
#define  ASCII_SLASH 144 
#define  ASCII_X 143 
#define  ASCII_a 142 
#define  ASCII_c 141 
#define  ASCII_e 140 
#define  ASCII_g 139 
#define  ASCII_h 138 
#define  ASCII_l 137 
#define  ASCII_m 136 
#define  ASCII_n 135 
#define  ASCII_o 134 
#define  ASCII_p 133 
#define  ASCII_r 132 
#define  ASCII_s 131 
#define  ASCII_t 130 
#define  ASCII_w 129 
#define  ASCII_x 128 
 int EXPAND_SPARE ; 
 int /*<<< orphan*/  FREE (TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ MALLOC (TYPE_2__*,int) ; 
 scalar_t__ REALLOC (TYPE_2__*,char*,int) ; 
 int XML_ERROR_NONE ; 
 int XML_ERROR_NO_MEMORY ; 
 int XML_ERROR_RESERVED_NAMESPACE_URI ; 
 int XML_ERROR_RESERVED_PREFIX_XML ; 
 int XML_ERROR_RESERVED_PREFIX_XMLNS ; 
 int XML_ERROR_UNDECLARING_PREFIX ; 
 int XML_FALSE ; 
 char const XML_T (char const) ; 
 int XML_TRUE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,char const*) ; 

__attribute__((used)) static enum XML_Error
addBinding(XML_Parser parser, PREFIX *prefix, const ATTRIBUTE_ID *attId,
           const XML_Char *uri, BINDING **bindingsPtr)
{
  static const XML_Char xmlNamespace[] = {
    ASCII_h, ASCII_t, ASCII_t, ASCII_p, ASCII_COLON, ASCII_SLASH, ASCII_SLASH,
    ASCII_w, ASCII_w, ASCII_w, ASCII_PERIOD, ASCII_w, ASCII_3, ASCII_PERIOD,
    ASCII_o, ASCII_r, ASCII_g, ASCII_SLASH, ASCII_X, ASCII_M, ASCII_L,
    ASCII_SLASH, ASCII_1, ASCII_9, ASCII_9, ASCII_8, ASCII_SLASH,
    ASCII_n, ASCII_a, ASCII_m, ASCII_e, ASCII_s, ASCII_p, ASCII_a, ASCII_c,
    ASCII_e, '\0'
  };
  static const int xmlLen =
    (int)sizeof(xmlNamespace)/sizeof(XML_Char) - 1;
  static const XML_Char xmlnsNamespace[] = {
    ASCII_h, ASCII_t, ASCII_t, ASCII_p, ASCII_COLON, ASCII_SLASH, ASCII_SLASH,
    ASCII_w, ASCII_w, ASCII_w, ASCII_PERIOD, ASCII_w, ASCII_3, ASCII_PERIOD,
    ASCII_o, ASCII_r, ASCII_g, ASCII_SLASH, ASCII_2, ASCII_0, ASCII_0,
    ASCII_0, ASCII_SLASH, ASCII_x, ASCII_m, ASCII_l, ASCII_n, ASCII_s,
    ASCII_SLASH, '\0'
  };
  static const int xmlnsLen =
    (int)sizeof(xmlnsNamespace)/sizeof(XML_Char) - 1;

  XML_Bool mustBeXML = XML_FALSE;
  XML_Bool isXML = XML_TRUE;
  XML_Bool isXMLNS = XML_TRUE;

  BINDING *b;
  int len;

  /* empty URI is only valid for default namespace per XML NS 1.0 (not 1.1) */
  if (*uri == XML_T('\0') && prefix->name)
    return XML_ERROR_UNDECLARING_PREFIX;

  if (prefix->name
      && prefix->name[0] == XML_T(ASCII_x)
      && prefix->name[1] == XML_T(ASCII_m)
      && prefix->name[2] == XML_T(ASCII_l)) {

    /* Not allowed to bind xmlns */
    if (prefix->name[3] == XML_T(ASCII_n)
        && prefix->name[4] == XML_T(ASCII_s)
        && prefix->name[5] == XML_T('\0'))
      return XML_ERROR_RESERVED_PREFIX_XMLNS;

    if (prefix->name[3] == XML_T('\0'))
      mustBeXML = XML_TRUE;
  }

  for (len = 0; uri[len]; len++) {
    if (isXML && (len > xmlLen || uri[len] != xmlNamespace[len]))
      isXML = XML_FALSE;

    if (!mustBeXML && isXMLNS
        && (len > xmlnsLen || uri[len] != xmlnsNamespace[len]))
      isXMLNS = XML_FALSE;
  }
  isXML = isXML && len == xmlLen;
  isXMLNS = isXMLNS && len == xmlnsLen;

  if (mustBeXML != isXML)
    return mustBeXML ? XML_ERROR_RESERVED_PREFIX_XML
                     : XML_ERROR_RESERVED_NAMESPACE_URI;

  if (isXMLNS)
    return XML_ERROR_RESERVED_NAMESPACE_URI;

  if (parser->m_namespaceSeparator)
    len++;
  if (parser->m_freeBindingList) {
    b = parser->m_freeBindingList;
    if (len > b->uriAlloc) {
      XML_Char *temp = (XML_Char *)REALLOC(parser, b->uri,
                          sizeof(XML_Char) * (len + EXPAND_SPARE));
      if (temp == NULL)
        return XML_ERROR_NO_MEMORY;
      b->uri = temp;
      b->uriAlloc = len + EXPAND_SPARE;
    }
    parser->m_freeBindingList = b->nextTagBinding;
  }
  else {
    b = (BINDING *)MALLOC(parser, sizeof(BINDING));
    if (!b)
      return XML_ERROR_NO_MEMORY;
    b->uri = (XML_Char *)MALLOC(parser, sizeof(XML_Char) * (len + EXPAND_SPARE));
    if (!b->uri) {
      FREE(parser, b);
      return XML_ERROR_NO_MEMORY;
    }
    b->uriAlloc = len + EXPAND_SPARE;
  }
  b->uriLen = len;
  memcpy(b->uri, uri, len * sizeof(XML_Char));
  if (parser->m_namespaceSeparator)
    b->uri[len - 1] = parser->m_namespaceSeparator;
  b->prefix = prefix;
  b->attId = attId;
  b->prevPrefixBinding = prefix->binding;
  /* NULL binding when default namespace undeclared */
  if (*uri == XML_T('\0') && prefix == &parser->m_dtd->defaultPrefix)
    prefix->binding = NULL;
  else
    prefix->binding = b;
  b->nextTagBinding = *bindingsPtr;
  *bindingsPtr = b;
  /* if attId == NULL then we are not starting a namespace scope */
  if (attId && parser->m_startNamespaceDeclHandler)
    parser->m_startNamespaceDeclHandler(parser->m_handlerArg, prefix->name,
                              prefix->binding ? uri : 0);
  return XML_ERROR_NONE;
}