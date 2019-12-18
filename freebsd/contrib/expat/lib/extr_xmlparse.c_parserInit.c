#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* XML_Parser ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_4__ {int /*<<< orphan*/  parsing; } ;
struct TYPE_5__ {scalar_t__ m_hash_secret_salt; int /*<<< orphan*/  m_paramEntityParsing; void* m_useForeignDTD; void* m_isParamEntity; TYPE_1__ m_parsingStatus; int /*<<< orphan*/ * m_parentParser; int /*<<< orphan*/ * m_unknownEncodingData; int /*<<< orphan*/ * m_unknownEncodingRelease; int /*<<< orphan*/ * m_unknownEncodingMem; scalar_t__ m_nSpecifiedAtts; int /*<<< orphan*/ * m_inheritedBindings; int /*<<< orphan*/ * m_tagStack; scalar_t__ m_tagLevel; int /*<<< orphan*/  m_defaultExpandInternalEntities; int /*<<< orphan*/ * m_openInternalEntities; int /*<<< orphan*/ * m_positionPtr; int /*<<< orphan*/ * m_eventEndPtr; int /*<<< orphan*/ * m_eventPtr; int /*<<< orphan*/  m_errorCode; int /*<<< orphan*/  m_position; void* m_declAttributeIsId; void* m_declAttributeIsCdata; int /*<<< orphan*/ * m_declNotationPublicId; int /*<<< orphan*/ * m_declNotationName; int /*<<< orphan*/ * m_declAttributeType; int /*<<< orphan*/ * m_doctypePubid; int /*<<< orphan*/ * m_doctypeSysid; int /*<<< orphan*/ * m_doctypeName; int /*<<< orphan*/ * m_declEntity; int /*<<< orphan*/ * m_declAttributeId; int /*<<< orphan*/ * m_declElementType; int /*<<< orphan*/ * m_parseEndPtr; scalar_t__ m_parseEndByteIndex; int /*<<< orphan*/  m_buffer; int /*<<< orphan*/  m_bufferEnd; int /*<<< orphan*/  m_bufferPtr; int /*<<< orphan*/ * m_xmlDeclHandler; int /*<<< orphan*/ * m_entityDeclHandler; int /*<<< orphan*/ * m_attlistDeclHandler; int /*<<< orphan*/ * m_elementDeclHandler; int /*<<< orphan*/ * m_skippedEntityHandler; struct TYPE_5__* m_externalEntityRefHandlerArg; int /*<<< orphan*/ * m_externalEntityRefHandler; int /*<<< orphan*/ * m_notStandaloneHandler; int /*<<< orphan*/ * m_endNamespaceDeclHandler; int /*<<< orphan*/ * m_startNamespaceDeclHandler; int /*<<< orphan*/ * m_notationDeclHandler; int /*<<< orphan*/ * m_unparsedEntityDeclHandler; int /*<<< orphan*/ * m_endDoctypeDeclHandler; int /*<<< orphan*/ * m_startDoctypeDeclHandler; int /*<<< orphan*/ * m_defaultHandler; int /*<<< orphan*/ * m_endCdataSectionHandler; int /*<<< orphan*/ * m_startCdataSectionHandler; int /*<<< orphan*/ * m_commentHandler; int /*<<< orphan*/ * m_processingInstructionHandler; int /*<<< orphan*/ * m_characterDataHandler; int /*<<< orphan*/ * m_endElementHandler; int /*<<< orphan*/ * m_startElementHandler; int /*<<< orphan*/ * m_handlerArg; int /*<<< orphan*/ * m_userData; int /*<<< orphan*/  m_encoding; int /*<<< orphan*/  m_initEncoding; int /*<<< orphan*/ * m_curBase; int /*<<< orphan*/  m_mem; int /*<<< orphan*/  m_protocolEncodingName; int /*<<< orphan*/  m_prologState; int /*<<< orphan*/  m_processor; } ;
typedef  int /*<<< orphan*/  POSITION ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ERROR_NONE ; 
 void* XML_FALSE ; 
 int /*<<< orphan*/  XML_INITIALIZED ; 
 int /*<<< orphan*/  XML_PARAM_ENTITY_PARSING_NEVER ; 
 int /*<<< orphan*/  XML_TRUE ; 
 int /*<<< orphan*/  XmlInitEncoding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmlPrologStateInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copyString (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prologInitProcessor ; 

__attribute__((used)) static void
parserInit(XML_Parser parser, const XML_Char *encodingName)
{
  parser->m_processor = prologInitProcessor;
  XmlPrologStateInit(&parser->m_prologState);
  if (encodingName != NULL) {
    parser->m_protocolEncodingName = copyString(encodingName, &(parser->m_mem));
  }
  parser->m_curBase = NULL;
  XmlInitEncoding(&parser->m_initEncoding, &parser->m_encoding, 0);
  parser->m_userData = NULL;
  parser->m_handlerArg = NULL;
  parser->m_startElementHandler = NULL;
  parser->m_endElementHandler = NULL;
  parser->m_characterDataHandler = NULL;
  parser->m_processingInstructionHandler = NULL;
  parser->m_commentHandler = NULL;
  parser->m_startCdataSectionHandler = NULL;
  parser->m_endCdataSectionHandler = NULL;
  parser->m_defaultHandler = NULL;
  parser->m_startDoctypeDeclHandler = NULL;
  parser->m_endDoctypeDeclHandler = NULL;
  parser->m_unparsedEntityDeclHandler = NULL;
  parser->m_notationDeclHandler = NULL;
  parser->m_startNamespaceDeclHandler = NULL;
  parser->m_endNamespaceDeclHandler = NULL;
  parser->m_notStandaloneHandler = NULL;
  parser->m_externalEntityRefHandler = NULL;
  parser->m_externalEntityRefHandlerArg = parser;
  parser->m_skippedEntityHandler = NULL;
  parser->m_elementDeclHandler = NULL;
  parser->m_attlistDeclHandler = NULL;
  parser->m_entityDeclHandler = NULL;
  parser->m_xmlDeclHandler = NULL;
  parser->m_bufferPtr = parser->m_buffer;
  parser->m_bufferEnd = parser->m_buffer;
  parser->m_parseEndByteIndex = 0;
  parser->m_parseEndPtr = NULL;
  parser->m_declElementType = NULL;
  parser->m_declAttributeId = NULL;
  parser->m_declEntity = NULL;
  parser->m_doctypeName = NULL;
  parser->m_doctypeSysid = NULL;
  parser->m_doctypePubid = NULL;
  parser->m_declAttributeType = NULL;
  parser->m_declNotationName = NULL;
  parser->m_declNotationPublicId = NULL;
  parser->m_declAttributeIsCdata = XML_FALSE;
  parser->m_declAttributeIsId = XML_FALSE;
  memset(&parser->m_position, 0, sizeof(POSITION));
  parser->m_errorCode = XML_ERROR_NONE;
  parser->m_eventPtr = NULL;
  parser->m_eventEndPtr = NULL;
  parser->m_positionPtr = NULL;
  parser->m_openInternalEntities = NULL;
  parser->m_defaultExpandInternalEntities = XML_TRUE;
  parser->m_tagLevel = 0;
  parser->m_tagStack = NULL;
  parser->m_inheritedBindings = NULL;
  parser->m_nSpecifiedAtts = 0;
  parser->m_unknownEncodingMem = NULL;
  parser->m_unknownEncodingRelease = NULL;
  parser->m_unknownEncodingData = NULL;
  parser->m_parentParser = NULL;
  parser->m_parsingStatus.parsing = XML_INITIALIZED;
#ifdef XML_DTD
  parser->m_isParamEntity = XML_FALSE;
  parser->m_useForeignDTD = XML_FALSE;
  parser->m_paramEntityParsing = XML_PARAM_ENTITY_PARSING_NEVER;
#endif
  parser->m_hash_secret_salt = 0;
}