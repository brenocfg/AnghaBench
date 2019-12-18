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
typedef  int /*<<< orphan*/  rxml_document_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  print_siblings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxml_free_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rxml_load_document (char const*) ; 
 int /*<<< orphan*/  rxml_root_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void rxml_log_document(const char *path)
{
   rxml_document_t *doc = rxml_load_document(path);
   if (!doc)
   {
      fprintf(stderr, "rxml: Failed to load document: %s\n", path);
      return;
   }

   print_siblings(rxml_root_node(doc), 0);
   rxml_free_document(doc);
}