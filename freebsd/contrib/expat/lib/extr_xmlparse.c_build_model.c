#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XML_Parser ;
typedef  int /*<<< orphan*/  XML_Content ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_7__ {int scaffCount; int contentStringLen; } ;
struct TYPE_6__ {TYPE_2__* m_dtd; } ;
typedef  TYPE_2__ DTD ;

/* Variables and functions */
 scalar_t__ MALLOC (TYPE_1__*,int) ; 
 int /*<<< orphan*/  build_node (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static XML_Content *
build_model (XML_Parser parser)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  XML_Content *ret;
  XML_Content *cpos;
  XML_Char * str;
  int allocsize = (dtd->scaffCount * sizeof(XML_Content)
                   + (dtd->contentStringLen * sizeof(XML_Char)));

  ret = (XML_Content *)MALLOC(parser, allocsize);
  if (!ret)
    return NULL;

  str =  (XML_Char *) (&ret[dtd->scaffCount]);
  cpos = &ret[1];

  build_node(parser, 0, ret, &cpos, &str);
  return ret;
}