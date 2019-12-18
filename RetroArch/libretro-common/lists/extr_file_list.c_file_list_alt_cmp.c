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
struct item_file {char* alt; char* path; } ;

/* Variables and functions */
 int strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int file_list_alt_cmp(const void *a_, const void *b_)
{
   const struct item_file *a = (const struct item_file*)a_;
   const struct item_file *b = (const struct item_file*)b_;
   const char *cmp_a         = a->alt ? a->alt : a->path;
   const char *cmp_b         = b->alt ? b->alt : b->path;
   return strcasecmp(cmp_a, cmp_b);
}