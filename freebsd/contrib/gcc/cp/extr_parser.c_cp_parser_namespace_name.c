#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ cp_parser_identifier (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_lookup_name (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_uncommitted_to_tentative_parse_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  none_type ; 

__attribute__((used)) static tree
cp_parser_namespace_name (cp_parser* parser)
{
  tree identifier;
  tree namespace_decl;

  /* Get the name of the namespace.  */
  identifier = cp_parser_identifier (parser);
  if (identifier == error_mark_node)
    return error_mark_node;

  /* Look up the identifier in the currently active scope.  Look only
     for namespaces, due to:

       [basic.lookup.udir]

       When looking up a namespace-name in a using-directive or alias
       definition, only namespace names are considered.

     And:

       [basic.lookup.qual]

       During the lookup of a name preceding the :: scope resolution
       operator, object, function, and enumerator names are ignored.

     (Note that cp_parser_class_or_namespace_name only calls this
     function if the token after the name is the scope resolution
     operator.)  */
  namespace_decl = cp_parser_lookup_name (parser, identifier,
					  none_type,
					  /*is_template=*/false,
					  /*is_namespace=*/true,
					  /*check_dependency=*/true,
					  /*ambiguous_decls=*/NULL);
  /* If it's not a namespace, issue an error.  */
  if (namespace_decl == error_mark_node
      || TREE_CODE (namespace_decl) != NAMESPACE_DECL)
    {
      if (!cp_parser_uncommitted_to_tentative_parse_p (parser))
	error ("%qD is not a namespace-name", identifier);
      cp_parser_error (parser, "expected namespace-name");
      namespace_decl = error_mark_node;
    }

  return namespace_decl;
}