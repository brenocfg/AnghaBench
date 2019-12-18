#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* next; } ;
typedef  TYPE_1__ mc_node_lang ;
struct TYPE_13__ {struct TYPE_13__* next; TYPE_1__* sub; } ;
typedef  TYPE_2__ mc_node ;
typedef  TYPE_1__ mc_keyword ;

/* Variables and functions */
 TYPE_1__* enum_facility (int) ; 
 TYPE_1__* enum_severity (int) ; 
 TYPE_1__** mc_facility_codes ; 
 int mc_facility_codes_count ; 
 TYPE_2__* mc_nodes ; 
 TYPE_1__** mc_nodes_lang ; 
 int mc_nodes_lang_count ; 
 TYPE_1__** mc_severity_codes ; 
 int mc_severity_codes_count ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_keyword_by_nval ; 
 int /*<<< orphan*/  sort_mc_node_lang ; 
 TYPE_1__** xmalloc (int) ; 

__attribute__((used)) static void
do_sorts (void)
{
  mc_node *h;
  mc_node_lang *n;
  const mc_keyword *k;
  int i;

  /* Sort message by their language and id ascending.  */
  mc_nodes_lang_count = 0;

  h = mc_nodes;
  while (h != NULL)
    {
      n = h->sub;
      while (n != NULL)
	{
	  mc_nodes_lang_count +=1;
	  n = n->next;
	}
      h = h->next;
    }

  if (mc_nodes_lang_count != 0)
    {
      h = mc_nodes;
      i = 0;
      mc_nodes_lang = xmalloc (sizeof (mc_node_lang *) * mc_nodes_lang_count);

      while (h != NULL)
	{
	  n = h->sub;
	  while (n != NULL)
	    {
	      mc_nodes_lang[i++] = n;
	      n = n->next;
	    }
	  h = h->next;
	}
      qsort (mc_nodes_lang, (size_t) mc_nodes_lang_count, sizeof (mc_node_lang *), sort_mc_node_lang);
    }
  /* Sort facility code definitions by there id ascending.  */
  i = 0;
  while ((k = enum_facility (i)) != NULL)
    ++i;
  mc_facility_codes_count = i;
  if (i != 0)
    {
      mc_facility_codes = xmalloc (sizeof (mc_keyword *) * i);
      i = 0;
      while ((k = enum_facility (i)) != NULL)
	mc_facility_codes[i++] = (mc_keyword *) k;
      qsort (mc_facility_codes, (size_t) mc_facility_codes_count, sizeof (mc_keyword *), sort_keyword_by_nval);
    }

  /* Sort severity code definitions by there id ascending.  */
  i = 0;
  while ((k = enum_severity (i)) != NULL)
    ++i;
  mc_severity_codes_count = i;
  if (i != 0)
    {
      mc_severity_codes = xmalloc (sizeof (mc_keyword *) * i);
      i = 0;
      while ((k = enum_severity (i)) != NULL)
	mc_severity_codes[i++] = (mc_keyword *) k;
      qsort (mc_severity_codes, (size_t) mc_severity_codes_count, sizeof (mc_keyword *), sort_keyword_by_nval);
    }
}