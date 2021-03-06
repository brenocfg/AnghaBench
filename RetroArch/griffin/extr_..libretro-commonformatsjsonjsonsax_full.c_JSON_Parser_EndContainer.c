#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Parser_PopMemberNameList (TYPE_1__*) ; 
 int /*<<< orphan*/  PARSER_TRACK_OBJECT_MEMBERS ; 

__attribute__((used)) static void JSON_Parser_EndContainer(JSON_Parser parser, int isObject)
{
   parser->depth--;
   if (isObject && GET_FLAGS(parser->flags, PARSER_TRACK_OBJECT_MEMBERS))
   {
      JSON_Parser_PopMemberNameList(parser);
   }
}