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
struct TYPE_6__ {int /*<<< orphan*/  userData; scalar_t__ (* realloc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_8__ {TYPE_2__* pMemberNames; TYPE_1__ memorySuite; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pFirstName; struct TYPE_7__* pAncestor; } ;
typedef  TYPE_2__ MemberNames ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_3__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Error_OutOfMemory ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtCodepoint (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Success ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static JSON_Status JSON_Parser_PushMemberNameList(JSON_Parser parser)
{
   MemberNames* pNames = (MemberNames*)parser->memorySuite.realloc(
         parser->memorySuite.userData, NULL, sizeof(MemberNames));

   if (!pNames)
   {
      JSON_Parser_SetErrorAtCodepoint(parser, JSON_Error_OutOfMemory);
      return JSON_Failure;
   }

   pNames->pAncestor    = parser->pMemberNames;
   pNames->pFirstName   = NULL;
   parser->pMemberNames = pNames;
   return JSON_Success;
}