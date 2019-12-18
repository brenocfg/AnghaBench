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
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ BASELINK_P (scalar_t__) ; 
 scalar_t__ cp_parser_id_expression (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static tree
cp_parser_declarator_id (cp_parser* parser, bool optional_p)
{
  tree id;
  /* The expression must be an id-expression.  Assume that qualified
     names are the names of types so that:

       template <class T>
       int S<T>::R::i = 3;

     will work; we must treat `S<T>::R' as the name of a type.
     Similarly, assume that qualified names are templates, where
     required, so that:

       template <class T>
       int S<T>::R<T>::i = 3;

     will work, too.  */
  id = cp_parser_id_expression (parser,
				/*template_keyword_p=*/false,
				/*check_dependency_p=*/false,
				/*template_p=*/NULL,
				/*declarator_p=*/true,
				optional_p);
  if (id && BASELINK_P (id))
    id = BASELINK_FUNCTIONS (id);
  return id;
}