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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rxml_log_document (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      fprintf(stderr, "Usage: %s <path>\n", argv[0]);
      return 1;
   }

   rxml_log_document(argv[1]);
}