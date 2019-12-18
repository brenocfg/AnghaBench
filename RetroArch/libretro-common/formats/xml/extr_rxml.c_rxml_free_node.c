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
struct rxml_node {struct rxml_node* data; struct rxml_node* name; struct rxml_node* value; struct rxml_node* attrib; scalar_t__ next; struct rxml_node* children; } ;
struct rxml_attrib_node {struct rxml_attrib_node* data; struct rxml_attrib_node* name; struct rxml_attrib_node* value; struct rxml_attrib_node* attrib; scalar_t__ next; struct rxml_attrib_node* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rxml_node*) ; 

__attribute__((used)) static void rxml_free_node(struct rxml_node *node)
{
   struct rxml_node *head = NULL;
   struct rxml_attrib_node *attrib_node_head = NULL;

   if (!node)
      return;

   for (head = node->children; head; )
   {
      struct rxml_node *next_node = (struct rxml_node*)head->next;
      rxml_free_node(head);
      head = next_node;
   }

   for (attrib_node_head = node->attrib; attrib_node_head; )
   {
      struct rxml_attrib_node *next_attrib = NULL;

      next_attrib = (struct rxml_attrib_node*)attrib_node_head->next;

      if (next_attrib)
      {
         if (attrib_node_head->attrib)
            free(attrib_node_head->attrib);
         if (attrib_node_head->value)
            free(attrib_node_head->value);
         if (attrib_node_head)
            free(attrib_node_head);
      }

      attrib_node_head = next_attrib;
   }

   if (node->name)
      free(node->name);
   if (node->data)
      free(node->data);
   if (node)
      free(node);
}