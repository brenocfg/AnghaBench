#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_11__ {int /*<<< orphan*/  scope; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 scalar_t__ cp_parser_class_name (TYPE_1__*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ cp_parser_identifier (TYPE_1__*) ; 
 scalar_t__ cp_parser_lookup_name_simple (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_name_lookup_error (TYPE_1__*,scalar_t__,scalar_t__,char*) ; 
 scalar_t__ cp_parser_objc_protocol_refs_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_1__*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  maybe_note_name_used_in_class (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  none_type ; 
 scalar_t__ objc_get_protocol_qualified_type (scalar_t__,scalar_t__) ; 
 scalar_t__ objc_is_class_name (scalar_t__) ; 
 scalar_t__ objc_is_id (scalar_t__) ; 

__attribute__((used)) static tree
cp_parser_type_name (cp_parser* parser)
{
  tree type_decl;
  tree identifier;

  /* We can't know yet whether it is a class-name or not.  */
  cp_parser_parse_tentatively (parser);
  /* Try a class-name.  */
  type_decl = cp_parser_class_name (parser,
				    /*typename_keyword_p=*/false,
				    /*template_keyword_p=*/false,
				    none_type,
				    /*check_dependency_p=*/true,
				    /*class_head_p=*/false,
				    /*is_declaration=*/false);
  /* If it's not a class-name, keep looking.  */
  if (!cp_parser_parse_definitely (parser))
    {
      /* It must be a typedef-name or an enum-name.  */
      identifier = cp_parser_identifier (parser);
      if (identifier == error_mark_node)
	return error_mark_node;

      /* Look up the type-name.  */
      type_decl = cp_parser_lookup_name_simple (parser, identifier);

      if (TREE_CODE (type_decl) != TYPE_DECL
	  && (objc_is_id (identifier) || objc_is_class_name (identifier)))
	{
	  /* See if this is an Objective-C type.  */
	  tree protos = cp_parser_objc_protocol_refs_opt (parser);
	  tree type = objc_get_protocol_qualified_type (identifier, protos);
	  if (type)
	    type_decl = TYPE_NAME (type);
	}

      /* Issue an error if we did not find a type-name.  */
      if (TREE_CODE (type_decl) != TYPE_DECL)
	{
	  if (!cp_parser_simulate_error (parser))
	    cp_parser_name_lookup_error (parser, identifier, type_decl,
					 "is not a type");
	  type_decl = error_mark_node;
	}
      /* Remember that the name was used in the definition of the
	 current class so that we can check later to see if the
	 meaning would have been different after the class was
	 entirely defined.  */
      else if (type_decl != error_mark_node
	       && !parser->scope)
	maybe_note_name_used_in_class (identifier, type_decl);
    }

  return type_decl;
}