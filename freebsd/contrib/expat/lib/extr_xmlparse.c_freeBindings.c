#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* XML_Parser ;
struct TYPE_8__ {int /*<<< orphan*/  prevPrefixBinding; TYPE_1__* prefix; struct TYPE_8__* nextTagBinding; } ;
struct TYPE_7__ {TYPE_3__* m_freeBindingList; int /*<<< orphan*/  m_handlerArg; int /*<<< orphan*/  (* m_endNamespaceDeclHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  binding; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ BINDING ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
freeBindings(XML_Parser parser, BINDING *bindings)
{
  while (bindings) {
    BINDING *b = bindings;

    /* m_startNamespaceDeclHandler will have been called for this
     * binding in addBindings(), so call the end handler now.
     */
    if (parser->m_endNamespaceDeclHandler)
        parser->m_endNamespaceDeclHandler(parser->m_handlerArg, b->prefix->name);

    bindings = bindings->nextTagBinding;
    b->nextTagBinding = parser->m_freeBindingList;
    parser->m_freeBindingList = b;
    b->prefix->binding = b->prevPrefixBinding;
  }
}