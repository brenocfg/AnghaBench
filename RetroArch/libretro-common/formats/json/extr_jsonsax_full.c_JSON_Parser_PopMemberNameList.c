#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  userData; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_10__ {TYPE_2__* pMemberNames; TYPE_1__ memorySuite; } ;
struct TYPE_9__ {struct TYPE_9__* pFirstName; struct TYPE_9__* pNextName; struct TYPE_9__* pAncestor; } ;
typedef  TYPE_2__ MemberNames ;
typedef  TYPE_2__ MemberName ;
typedef  TYPE_4__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void JSON_Parser_PopMemberNameList(JSON_Parser parser)
{
   MemberNames* pAncestor = parser->pMemberNames->pAncestor;
   while (parser->pMemberNames->pFirstName)
   {
      MemberName* pNextName = parser->pMemberNames->pFirstName->pNextName;
      parser->memorySuite.free(parser->memorySuite.userData, parser->pMemberNames->pFirstName);
      parser->pMemberNames->pFirstName = pNextName;
   }
   parser->memorySuite.free(parser->memorySuite.userData, parser->pMemberNames);
   parser->pMemberNames = pAncestor;
}