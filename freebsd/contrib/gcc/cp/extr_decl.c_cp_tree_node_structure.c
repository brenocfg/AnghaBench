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
union lang_tree_node {int /*<<< orphan*/  generic; } ;
typedef  enum cp_tree_node_structure_enum { ____Placeholder_cp_tree_node_structure_enum } cp_tree_node_structure_enum ;

/* Variables and functions */
#define  BASELINK 134 
#define  DEFAULT_ARG 133 
#define  IDENTIFIER_NODE 132 
#define  OVERLOAD 131 
#define  PTRMEM_CST 130 
#define  TEMPLATE_PARM_INDEX 129 
#define  TINST_LEVEL 128 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
 int TS_CP_BASELINK ; 
 int TS_CP_DEFAULT_ARG ; 
 int TS_CP_GENERIC ; 
 int TS_CP_IDENTIFIER ; 
 int TS_CP_OVERLOAD ; 
 int TS_CP_PTRMEM ; 
 int TS_CP_TINST_LEVEL ; 
 int TS_CP_TPI ; 

enum cp_tree_node_structure_enum
cp_tree_node_structure (union lang_tree_node * t)
{
  switch (TREE_CODE (&t->generic))
    {
    case DEFAULT_ARG:		return TS_CP_DEFAULT_ARG;
    case IDENTIFIER_NODE:	return TS_CP_IDENTIFIER;
    case OVERLOAD:		return TS_CP_OVERLOAD;
    case TEMPLATE_PARM_INDEX:	return TS_CP_TPI;
    case TINST_LEVEL:		return TS_CP_TINST_LEVEL;
    case PTRMEM_CST:		return TS_CP_PTRMEM;
    case BASELINK:		return TS_CP_BASELINK;
    default:			return TS_CP_GENERIC;
    }
}