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
struct TYPE_4__ {scalar_t__ root_node; } ;
typedef  TYPE_1__ rxml_document_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  rxml_free_node (scalar_t__) ; 

void rxml_free_document(rxml_document_t *doc)
{
   if (!doc)
      return;

   if (doc->root_node)
      rxml_free_node(doc->root_node);

   free(doc);
}