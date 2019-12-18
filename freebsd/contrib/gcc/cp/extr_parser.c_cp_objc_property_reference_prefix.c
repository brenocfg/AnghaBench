#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_DOT ; 
 scalar_t__ c_dialect_objc () ; 
 TYPE_3__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ objc_is_class_name (int /*<<< orphan*/ ) ; 
 scalar_t__ objc_is_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cp_objc_property_reference_prefix (cp_parser *parser, tree type)
{
  return c_dialect_objc () && cp_lexer_peek_token (parser->lexer)->type == CPP_DOT 
  && (objc_is_id (type) || objc_is_class_name (type));
}