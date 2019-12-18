#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rxml_node {int dummy; } ;
struct TYPE_3__ {struct rxml_node* root_node; } ;
typedef  TYPE_1__ rxml_document_t ;

/* Variables and functions */

struct rxml_node *rxml_root_node(rxml_document_t *doc)
{
   if (doc)
      return doc->root_node;
   return NULL;
}