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
struct rxml_node {struct rxml_attrib_node* attrib; } ;
struct rxml_attrib_node {char const* value; int /*<<< orphan*/  attrib; struct rxml_attrib_node* next; } ;

/* Variables and functions */
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

const char *rxml_node_attrib(struct rxml_node *node, const char *attrib)
{
   struct rxml_attrib_node *attribs = NULL;
   for (attribs = node->attrib; attribs; attribs = attribs->next)
   {
      if (string_is_equal(attrib, attribs->attrib))
         return attribs->value;
   }

   return NULL;
}